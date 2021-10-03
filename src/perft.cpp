//
//  perft.cpp
//  My Engine
//
//  Created by Nikhil Arora on 10/2/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "perft.h"
#include <iostream>
#include "move.h"
#include "movegen.h"

// perft to test pseduolegal move generation
uint64_t perft(Board& board, int depth){
	if(depth == 0)
		return 1ULL;
	std::vector<Move> move_list;
	uint64_t nodes = 0;
	generateMoves(board, move_list);
	Color side = board.getSideToMove();
	for(size_t i = 0; i < move_list.size(); i++){
		board.makeMove(move_list[i]);
		if(!board.inCheck(side))
			nodes += perft(board, depth - 1);
		board.unmakeMove();
	}
	return nodes;
}

// perft driver code
uint64_t perft(int depth){
	Board board;
	return perft(board, depth);	
}

// perft with detailed information
PerftCounts detailedPerft(Board& board, int depth){
	if(depth == 0)
		return {1,0,0,0,0};
	std::vector<Move> move_list;
	PerftCounts pc = {0,0,0,0,0};
	generateMoves(board, move_list);
	Color side = board.getSideToMove();
	for(size_t i = 0; i < move_list.size(); i++){
		if(move_list[i].isCapture())
			pc.captures += 1;
		if(move_list[i].isPromotion())
			pc.promos += 1;
		if(move_list[i].isEnPassant())
			pc.en_passants += 1;
		if(move_list[i].isCastle())
			pc.castles += 1;
		board.makeMove(move_list[i]);
		if(!board.inCheck(side)){
			PerftCounts ret = detailedPerft(board, depth-1);
			pc.nodes += ret.nodes;
			pc.captures += ret.captures;
			pc.promos += ret.promos;
			pc.en_passants += ret.en_passants;
			pc.castles += ret.castles;
		}
		board.unmakeMove();
	}
	return pc;
}

// perft that counts moves found in subtrees starting at depth=1
void perftCount(Board& board, int depth){
	if(depth == 0)
		return;
	std::vector<Move> move_list;
	generateMoves(board, move_list);
	Color side = board.getSideToMove();
	for(size_t i = 0; i < move_list.size(); i++){
		uint64_t nodes = 0;
		board.makeMove(move_list[i]);
		if(!board.inCheck(side))
			nodes += perft(board, depth - 1);
		board.unmakeMove();
		if(nodes != 0)
			std::cout << (std::string)move_list[i]<< ": " << nodes << std::endl;
	}
}