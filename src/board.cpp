//
//  board.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "board.h"
#include <iostream>
#include <fcntl.h>
#include "bitops.h"
#include "fen.h"

/* ---- BOARD CONSTRUCTORS ---- */

// default constructor
Board::Board(){
	m_pieces[(nAll << 1) + nWhite]     = WHITE_PIECES_START;
	m_pieces[(nAll << 1) + nBlack]     = BLACK_PIECES_START;
	m_pieces[(nPawn << 1) + nWhite]    = WHITE_PAWN_START;
	m_pieces[(nPawn << 1) + nBlack]    = BLACK_PAWN_START;
	m_pieces[(nKnight << 1) + nWhite]  = WHITE_KNIGHT_START;
	m_pieces[(nKnight << 1) + nBlack]  = BLACK_KNIGHT_START;
	m_pieces[(nBishop << 1) + nWhite]  = WHITE_BISHOP_START;
	m_pieces[(nBishop << 1) + nBlack]  = BLACK_BISHOP_START;
	m_pieces[(nRook << 1) + nWhite]    = WHITE_ROOK_START;
	m_pieces[(nRook << 1) + nBlack]    = BLACK_ROOK_START;
	m_pieces[(nQueen << 1) + nWhite]   = WHITE_QUEEN_START;
	m_pieces[(nQueen << 1) + nBlack]   = BLACK_QUEEN_START;
	m_pieces[(nKing << 1) + nWhite]    = WHITE_KING_START;
	m_pieces[(nKing << 1) + nBlack]    = BLACK_KING_START;
	m_side = nWhite;
	m_castle_ability[0] = true;
	m_castle_ability[1] = true;
	m_castle_ability[2] = true;
	m_castle_ability[3] = true;
	m_en_passant_target = none;
	m_half_moves = 0;
	m_num_moves = 1;
}

// construct board from bit board array
Board::Board(uint64_t pieces[NUM_BITBOARDS], Color side, 
	         bool castle_ability[4], Square en_passant_target, 
	         int half_moves, int num_moves){
	for(int i = 0; i < NUM_BITBOARDS; i++){
		m_pieces[i] = pieces[i];
	}
	m_side = side;
	m_castle_ability[0] = castle_ability[0];
	m_castle_ability[1] = castle_ability[1];
	m_castle_ability[2] = castle_ability[2];
	m_castle_ability[3] = castle_ability[3];
	m_en_passant_target = en_passant_target;
	m_half_moves = half_moves;
	m_num_moves = num_moves;
}

// copy constructor
Board::Board(const Board& other){
	m_side = other.m_side;
	m_castle_ability[0] = other.m_castle_ability[0];
	m_castle_ability[1] = other.m_castle_ability[1];
	m_castle_ability[2] = other.m_castle_ability[2];
	m_castle_ability[3] = other.m_castle_ability[3];
	m_en_passant_target = other.m_en_passant_target;
	m_half_moves = other.m_half_moves;
	m_num_moves = other.m_num_moves;
	for(int i = 0; i < NUM_BITBOARDS; i++){
		m_pieces[i] = other.m_pieces[i];
	}
}

// FEN string constructor
Board::Board(const std::string& FEN){
	Fen* f = parseFenString(FEN);
	if(f != nullptr){
		for(int i = 0; i < NUM_BITBOARDS; i++)
			m_pieces[i] = f->pieces[i];
		m_side = f->side;
		m_castle_ability[0] = f->castle_ability[0];
		m_castle_ability[1] = f->castle_ability[1];
		m_castle_ability[2] = f->castle_ability[2];
		m_castle_ability[3] = f->castle_ability[3];
		m_en_passant_target = f->en_passant_target;
		m_half_moves = f->half_moves;
		m_num_moves = f->num_moves;
		delete f;
	}
	else{
		std::cerr << "Error: unable to construct Board object from FEN string" << std::endl;
		exit(EXIT_FAILURE);
	}
}


/* ---- BIT BOARD GETTERS ---- */

// functions that get the piece and color bit boards 
// returns a bit board for a certain piece and color
uint64_t Board::getPieceBitBoard(const Piece& p, const Color& c) const{
	return m_pieces[(p << 1) + c];
}
// returns bit board for all pieces on the board
uint64_t Board::getAllPieces() const{
	return m_pieces[(nAll << 1) + nWhite] | m_pieces[nAll + nBlack];
}
// returns bit board for all empty squares on the board
uint64_t Board::getEmptySquares() const{
	return ~(m_pieces[(nAll << 1) + nWhite] | m_pieces[nAll + nBlack]);
}
// returns bit board for all pieces of the same color
uint64_t Board::getAllColorPieces(const Color& c) const{
	return m_pieces[(nAll << 1) + c];
}
// following functions return piece set of each piece for a given color
uint64_t Board::getPawns(const Color& c) const{
	return m_pieces[(nPawn << 1) + c];
}
uint64_t Board::getKnights(const Color& c) const{
	return m_pieces[(nKnight << 1) + c];
}
uint64_t Board::getBishops(const Color& c) const{
	return m_pieces[(nBishop << 1) + c];
}
uint64_t Board::getRooks(const Color& c) const{
	return m_pieces[(nRook << 1) + c];
}
uint64_t Board::getQueen(const Color& c) const{
	return m_pieces[(nQueen << 1) + c];
}
uint64_t Board::getKing(const Color& c) const{
	return m_pieces[(nKing << 1) + c];
}

/* ---- OTHER GETTERS ---- */
Color Board::getSideToMove() const{
	return m_side;
}
bool Board::getCastleAbility(const int& castle_side) const{
	if(castle_side >= 0 && castle_side < 4)
		return m_castle_ability[castle_side];
	return false;
}
Square Board::getEnPassantTarget() const{
	return m_en_passant_target;
}
int Board::getHalfMoves() const{
	return m_half_moves;
}
int Board::getNumMoves() const{
	return m_num_moves;
}






/* ---- PRINT FUNCTIONS ---- */
// print functions useful for debugging

// prints the whole board
void Board::printBoard() const{
	printBoard(getAllPieces());
}
// prints a given bit board according to the game state represented by this board
void Board::printBoard(const uint64_t& b) const{
	char board[NUM_RANKS][NUM_FILES];
	uint64_t bitmask = 1;
	for(int i = 0 ; i < NUM_RANKS; i++){
		for(int j = 0; j < NUM_FILES; j++){
			bool occupied = false;
			for(int p = nPawn; p <= nKing; p++){
				for(int c = nWhite; c <= nBlack; c++){
					if((bitmask & b & getPieceBitBoard((Piece)p, (Color)c)) != 0){
						board[i][j] = getPieceChar((Piece)p, (Color)c);
						occupied = true;
						break;
					}
				}
				if(occupied)
					break;
			}
			if(!occupied)
				board[i][j] = '*';
			bitmask = bitmask << 1;
		}
	}
	printBoardArray(board);
}
// prints all pieces of one color
void Board::printColorBitBoard(const Color& c) const{
	printBoard(getAllColorPieces(c));
}
// prints all pieces of one piece type and one color
void Board::printPieceBitBoard(const Piece& p, const Color& c) const{
	printBoard(getPieceBitBoard(p, c));
}
// prints every bit board
void Board::printAllBitBoards() const{
	for(int p = nAll; p <= nKing; p++){
		printPieceBitBoard((Piece)p, nWhite);
		std::cout << std::endl;
		printPieceBitBoard((Piece)p, nBlack);
		std::cout << std::endl;
	}
	printBoard();
}

// private helper print functions
// gets character representing a piece of a color
char Board::getPieceChar(const Piece& p, const Color& c) const{
	char pieceChar = '1';
	// use ascii characters to represent pieces
	if(c == nWhite){
		switch(p){
			case nPawn: pieceChar = 'P'; break;
			case nKnight: pieceChar = 'N'; break;
			case nBishop: pieceChar = 'B'; break;
			case nRook: pieceChar = 'R'; break;
			case nQueen: pieceChar = 'Q'; break;
			case nKing: pieceChar = 'K'; break;
			default: pieceChar = '1';
		}
	}
	else if(c == nBlack){
		switch(p){
			case nPawn: pieceChar = 'p'; break;
			case nKnight: pieceChar = 'n'; break;
			case nBishop: pieceChar = 'b'; break;
			case nRook: pieceChar = 'r'; break;
			case nQueen: pieceChar = 'q'; break;
			case nKing: pieceChar = 'k'; break;
			default: pieceChar = '1';
		}
	}
	return pieceChar;
}
// prints board array
void Board::printBoardArray(char board[NUM_RANKS][NUM_FILES]) const{
	for(int i = NUM_RANKS - 1; i >= 0; i--){
		for(int j = 0; j < NUM_FILES; j++){
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}	
}