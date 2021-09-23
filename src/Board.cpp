//
//  Board.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "headers/Board.h"
#include <iostream>
#include <fcntl.h>
using namespace std;

/* ---- BOARD CONSTRUCTORS ---- */

Board::Board(){
	m_pieces[(nAll << 1) + nWhite] = WhitePiecesStart;
	m_pieces[(nAll << 1) + nBlack] = BlackPiecesStart;
	m_pieces[(nPawn << 1) + nWhite] = WhitePawnStart;
	m_pieces[(nPawn << 1) + nBlack] = BlackPawnStart;
	m_pieces[(nKnight << 1) + nWhite] = WhiteKnightStart;
	m_pieces[(nKnight << 1) + nBlack] = BlackKnightStart;
	m_pieces[(nBishop << 1) + nWhite] = WhiteBishopStart;
	m_pieces[(nBishop << 1) + nBlack] = BlackBishopStart;
	m_pieces[(nRook << 1) + nWhite] = WhiteRookStart;
	m_pieces[(nRook << 1) + nBlack] = BlackRookStart;
	m_pieces[(nQueen << 1) + nWhite] = WhiteQueenStart;
	m_pieces[(nQueen << 1) + nBlack] = BlackQueenStart;
	m_pieces[(nKing << 1) + nWhite] = WhiteKingStart;
	m_pieces[(nKing << 1) + nBlack] = BlackKingStart;
}

Board::Board(uint64_t whitePieces, uint64_t blackPieces, uint64_t whitePawns, uint64_t blackPawns, 
		  uint64_t whiteKnights, uint64_t blackKnights, uint64_t whiteBishops, uint64_t blackBishops, 
		  uint64_t whiteRooks, uint64_t blackRooks, uint64_t whiteQueen, uint64_t blackQueen, 
		  uint64_t whiteKing, uint64_t blackKing){
	m_pieces[(nAll << 1) + nWhite] = whitePieces;
	m_pieces[(nAll << 1) + nBlack] = blackPieces;
	m_pieces[(nPawn << 1) + nWhite] = whitePawns;
	m_pieces[(nPawn << 1) + nBlack] = blackPawns;
	m_pieces[(nKnight << 1) + nWhite] = whiteKnights;
	m_pieces[(nKnight << 1) + nBlack] = blackKnights;
	m_pieces[(nBishop << 1) + nWhite] = whiteBishops;
	m_pieces[(nBishop << 1) + nBlack] = blackBishops;
	m_pieces[(nRook << 1) + nWhite] = whiteRooks;
	m_pieces[(nRook << 1) + nBlack] = blackRooks;
	m_pieces[(nQueen << 1) + nWhite] = whiteQueen;
	m_pieces[(nQueen << 1) + nBlack] = blackQueen;
	m_pieces[(nKing << 1) + nWhite] = whiteKing;
	m_pieces[(nKing << 1) + nBlack] = blackKing;
}



/* ---- BITBOARD GETTERS ---- */

// functions that get the piece and color bit boards 
// returns a bit board for a certain piece and color
uint64_t Board::getPieceBitBoard(const Piece& p, const Color& c) const{
	return m_pieces[(p << 1) + c];
}
// returns bit board for all pieces on the board
uint64_t Board::getAllPieces() const{
	return m_pieces[(nAll << 1) + nWhite] | m_pieces[nAll + nBlack];
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



/* ---- PRINT FUNCTIONS ---- */
// print functions useful for debugging

// prints the whole board
void Board::printWholeBoard(const bool& ascii) const{
	printBitBoard(getAllPieces(), ascii);
}
// prints a given bit board
void Board::printBitBoard(const uint64_t& bitboard, const bool& ascii) const{
	char board[NUM_RANKS][NUM_FILES];
	uint64_t bitmask = 1;
	for(int i = 0 ; i < NUM_RANKS; i++){
		for(int j = 0; j < NUM_FILES; j++){
			bool occupied = false;
			for(int p = nPawn; p <= nKing; p++){
				for(int c = nWhite; c <= nBlack; c++){
					if((bitmask & bitboard & getPieceBitBoard((Piece)p, (Color)c)) != 0){
						board[i][j] = getPieceChar((Piece)p, (Color)c, ascii);
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
	printBoardArray(board, ascii);
}
// prints all pieces of one color
void Board::printColorBitBoard(const Color& c, const bool& ascii) const{
	printBitBoard(getAllColorPieces(c), ascii);
}
// prints all pieces of one piece type and one color
void Board::printPieceBitBoard(const Piece& p, const Color& c, const bool& ascii) const{
	printBitBoard(getPieceBitBoard(p, c), ascii);
}
// prints every bit board
void Board::printBitBoards(const bool& ascii) const{
	for(int p = nAll; p <= nKing; p++){
		printPieceBitBoard((Piece)p, nWhite, ascii);
		cout << endl;
		printPieceBitBoard((Piece)p, nBlack, ascii);
		cout << endl;
	}
	printWholeBoard(ascii);
}
// gets character representing a piece of a color
char Board::getPieceChar(const Piece& p, const Color& c, const bool& ascii) const{
	char pieceChar = '1';
	// use ascii characters to represent pieces
	if(ascii){
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
	}
	// use unicode characters to represent pieces
	else{
		if(c == nWhite){
			switch(p){
				case nPawn: pieceChar = WhitePawnChar; break;
				case nKnight: pieceChar = WhiteKnightChar; break;
				case nBishop: pieceChar = WhiteBishopChar; break;
				case nRook: pieceChar = WhiteRookChar; break;
				case nQueen: pieceChar = WhiteQueenChar; break;
				case nKing: pieceChar = WhiteKingChar; break;
				default: pieceChar = '1';
			}
		}
		else if(c == nBlack){
			switch(p){
				case nPawn: pieceChar = BlackPawnChar; break;
				case nKnight: pieceChar = BlackKnightChar; break;
				case nBishop: pieceChar = BlackBishopChar; break;
				case nRook: pieceChar = BlackRookChar; break;
				case nQueen: pieceChar = BlackQueenChar; break;
				case nKing: pieceChar = BlackKingChar; break;
				default: pieceChar = '1';
			}
		}
	}
	return pieceChar;
}
// prints board array
void Board::printBoardArray(char board[NUM_RANKS][NUM_FILES], const bool& ascii) const{
	for(int i = NUM_RANKS - 1; i >= 0; i--){
		for(int j = 0; j < NUM_FILES; j++){
			cout << board[i][j];
		}
		cout << endl;
	}	
}