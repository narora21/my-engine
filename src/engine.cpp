//
//  engine.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "engine.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "move.h"
#include "movegen.h"
#include "bitops.h"
#include "fen.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
using namespace std::chrono;

/* ---- EVALUATION METHODS ---- */
float materialCount(const Board& b, Color side){
	float points = 0;
	points += (float)(PAWN_VALUE * populationCount(b.getPawns(side)));
	points += (float)(KNIGHT_VALUE * populationCount(b.getKnights(side)));
	points += (float)(BISHOP_VALUE * populationCount(b.getBishops(side)));
	points += (float)(ROOK_VALUE * populationCount(b.getRooks(side)));
	points += (float)(QUEEN_VALUE * populationCount(b.getQueens(side)));
	return points;
}

float badEvaluation(const Board& b){
	float score = materialCount(b, nWhite) - materialCount(b, nBlack);
	return score;
}


/* ---- SEARCH ALGORITHMS ---- */

// MINI MAX ALGORITHM
Eval minimax_helper(Board& board, int depth, float (*evaluate)(const Board&), bool maxPlayer){
	if(board.getHalfMoves() == 50) // 50 move rule
		return {0, Move(), 1ULL};
	if(depth == 0)
		return {evaluate(board), Move(), 1ULL};
	float inf = std::numeric_limits<float>::infinity();
	Color side = board.getSideToMove();
	uint64_t nodes_searched = 1ULL;
	Move best_move = Move();
	if(maxPlayer){
		float max_score = -inf;
		std::vector<Move> pseudo_legals;
		generateMoves(board, pseudo_legals);
		int legals = 0;
		for(size_t i = 0; i < pseudo_legals.size(); i++){
			if(pseudo_legals[i].isNone())
				continue;
			board.makeMove(pseudo_legals[i]);
			if(board.inCheck(side)){ // legality check
				board.unmakeMove();
				continue;
			}
			legals++;
			Eval eval = minimax_helper(board, depth - 1, evaluate, false);
			nodes_searched += eval.nodes_searched;
			if(eval.score > max_score){
				max_score = eval.score;
				best_move = pseudo_legals[i];
			}
			board.unmakeMove();
		}
		if(legals == 0 && !board.inCheck(side)) // stalemate
			return {0, best_move, nodes_searched};
		return {max_score, best_move, nodes_searched}; // return max score found
	}
	else{ // min player
		float min_score = inf;
		std::vector<Move> pseudo_legals;
		generateMoves(board, pseudo_legals);
		int legals = 0;
		for(size_t i = 0; i < pseudo_legals.size(); i++){
			if(pseudo_legals[i].isNone())
				continue;
			board.makeMove(pseudo_legals[i]);
			if(board.inCheck(side)){ // legality check
				board.unmakeMove();
				continue;
			}
			legals++;
			Eval eval = minimax_helper(board, depth - 1, evaluate, true);
			nodes_searched += eval.nodes_searched;
			if(eval.score < min_score){
				min_score = eval.score;
				best_move = pseudo_legals[i];
			}
			board.unmakeMove();
		}
		if(legals == 0 && !board.inCheck(side)) // stalemate
			return {0, best_move, nodes_searched};
		return {min_score, best_move, nodes_searched}; // return min score found
	}
}
Eval minimax(Board& board, int depth, float (*evaluate)(const Board&)){
	Color side = board.getSideToMove();
	if(side == nWhite) // white will maximize
		return minimax_helper(board, depth, evaluate, true);
	else // black will minimize
		return minimax_helper(board, depth, evaluate, false);
}

// MINI MAX WITH ALPHA BETA PRUNING
Eval alphabeta_helper(Board& board, int depth, float (*evaluate)(const Board&), float alpha, float beta, bool maxPlayer){
	if(board.getHalfMoves() == 50) // 50 move rule
		return {0, Move(), 1ULL};
	if(depth == 0)
		return {evaluate(board), Move(), 1ULL};
	float inf = std::numeric_limits<float>::infinity();
	Color side = board.getSideToMove();
	uint64_t nodes_searched = 1ULL;
	Move best_move = Move();
	if(maxPlayer){ // white will maximize
		float max_score = -inf;
		std::vector<Move> pseudo_legals;
		generateMoves(board, pseudo_legals);
		int legals = 0;
		for(size_t i = 0; i < pseudo_legals.size(); i++){
			if(pseudo_legals[i].isNone())
				continue;
			board.makeMove(pseudo_legals[i]);
			if(board.inCheck(side)){ // legality check
				board.unmakeMove();
				continue;
			}
			legals++;
			Eval eval = alphabeta_helper(board, depth - 1, evaluate, alpha, beta, false);
			nodes_searched += eval.nodes_searched;
			if(eval.score > max_score){
				max_score = eval.score;
				best_move = pseudo_legals[i];
			}
			board.unmakeMove();
			if(max_score >= beta)
				break; // prune rest of branches
			alpha = std::max(alpha, max_score);
		}
		if(legals == 0 && !board.inCheck(side)) // stalemate
			return {0, best_move, nodes_searched};
		return {max_score, best_move, nodes_searched}; // return max score found
	}
	else{ // black will minimize
		float min_score = inf;
		std::vector<Move> pseudo_legals;
		generateMoves(board, pseudo_legals);
		int legals = 0;
		for(size_t i = 0; i < pseudo_legals.size(); i++){
			if(pseudo_legals[i].isNone())
				continue;
			board.makeMove(pseudo_legals[i]);
			if(board.inCheck(side)){ // legality check
				board.unmakeMove();
				continue;
			}
			legals++;
			Eval eval = alphabeta_helper(board, depth - 1, evaluate, alpha, beta, true);
			nodes_searched += eval.nodes_searched;
			if(eval.score < min_score){
				min_score = eval.score;
				best_move = pseudo_legals[i];
			}
			board.unmakeMove();
			if(min_score <= alpha)
				break; // prune rest of branches
			beta = std::min(beta, min_score);
		}
		if(legals == 0 && !board.inCheck(side)) // stalemate
			return {0, best_move, nodes_searched};
		return {min_score, best_move, nodes_searched}; // return min score found
	} 
}
Eval alphabeta(Board& board, int depth, float (*evaluate)(const Board&)){
	float inf = std::numeric_limits<float>::infinity();
	float alpha = -inf;
	float beta = inf;
	Color side = board.getSideToMove();
	if(side == nWhite) // white will maximize
		return alphabeta_helper(board, depth, evaluate, alpha, beta, true);
	else // black will minimize
		return alphabeta_helper(board, depth, evaluate, alpha, beta, false);
}


/* ---- CORE ENGINE ---- */
// initialize engine pre-requisites
bool engineInitialized = false;
void init(){
	std::cout << "Initializing engine..." << std::endl;
	// compute piece attack tables
	initPawnAttacks();
	initKnightAttacks();
	initMagicBishopTable();
	initMagicRookTable();
	initKingAttacks();
	initInBetweens();
	engineInitialized = true;
}
void runEngine(){
	if(engineInitialized){
		while(true){
			std::cout << "Enter fen string: ";
			std::string fen;
			std::getline(std::cin, fen);
			if(!isValidFenString(fen)){
				std::cout << "Invalid fen string" << std::endl;
				continue;
			}
			Board board(fen);
			std::cout << "Enter search depth: ";
			int depth = 0;
			std::cin >> depth;
			if(depth < 0){
				std::cout << "Invalid depth supplied" << std::endl;
				continue;
			}
			Eval eval;
			/*
			std::cout << std::endl;
			std::cout << "Running MiniMax Algorithm..." << std::endl;
			auto minimax_start = high_resolution_clock::now();
			eval = minimax(board, depth, badEvaluation);
			auto minimax_stop = high_resolution_clock::now();
			auto minimax_duration = duration_cast<seconds>(minimax_stop - minimax_start);
			std::cout << "Time: " << ((double)minimax_duration.count()) << " s" << std::endl;
			std::cout << "Evaluation: " << eval.score << std::endl;
			std::cout << "Best Move: " << (std::string)eval.best_move << std::endl;
			std::cout << "Nodes Searched: " << eval.nodes_searched << std::endl;*/

			std::cout << std::endl;
			std::cout << "Running MiniMax with Alpha-Beta Pruning..." << std::endl;
			auto alphabeta_start = high_resolution_clock::now();
			eval = alphabeta(board, depth, badEvaluation);
			auto alphabeta_stop = high_resolution_clock::now();
			auto alphabeta_duration = duration_cast<seconds>(alphabeta_stop - alphabeta_start);
			std::cout << "Time: " << ((double)alphabeta_duration.count()) << " s" << std::endl;
			std::cout << "Evaluation: " << eval.score << std::endl;
			std::cout << "Best Move: " << (std::string)eval.best_move << std::endl;
			std::cout << "Nodes Searched: " << eval.nodes_searched << std::endl;

			std::cout << std::endl;
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
	}
	else{
		//error
		std::cerr << "Error: attempted to run engine before initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}