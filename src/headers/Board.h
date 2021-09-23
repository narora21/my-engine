//
//  Board.h
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef BOARD_H
#define BOARD_H

/* 

A chessboard is represented by a series of bit boards for each piece
The bit boards use a little-endian rank-file mapping 
The following compass rose identifies direction offsets:

  noWe         nort         noEa
          +7    +8    +9
              \  |  /
  west    -1 <-  0 -> +1    east
              /  |  \
          -9    -8    -7
  soWe         sout         soEa

The array of bitboards is defined to contain the following:
m_pieces:
	0:  All the white pieces
	1:  All the black pieces
	2:  White Pawns
	3:  Black Pawns
	4:  White Knights
	5:  Black Knights
	6:  White Bishops
	7:  Black Bishops
	8:  White Rooks
	9:  Black Rooks
	10: White Queen
	11: Black Queen
	12: White King
	13: Black King
These indices can be accessed by using a Piece and Color enum:
index = (Piece * 2) + Color = (Piece << 1) + Color
*/

#include <cstdint>
#include "Constants.h"

/* Board class: collection of bit boards for each piece */

class Board{
public:
	// builds a board at the starting position
	Board();
	// builds a board using given bit boards
	Board(uint64_t whitePieces, uint64_t blackPieces, uint64_t whitePawns, uint64_t blackPawns, 
		  uint64_t whiteKnights, uint64_t blackKnights, uint64_t whiteBishops, uint64_t blackBishops, 
		  uint64_t whiteRooks, uint64_t blackRooks, uint64_t whiteQueen, uint64_t blackQueen, 
		  uint64_t whiteKing, uint64_t blackKing);

  	// functions that get the piece bit boards
  	uint64_t getPieceBitBoard(const Piece& p, const Color& c) const;
  	uint64_t getAllPieces() const;
  	uint64_t getAllColorPieces(const Color& c) const;
  	uint64_t getPawns(const Color& c) const;
  	uint64_t getKnights(const Color& c) const;
  	uint64_t getBishops(const Color& c) const;
  	uint64_t getRooks(const Color& c) const;
  	uint64_t getQueen(const Color& c) const;
  	uint64_t getKing(const Color& c) const;

  	// print functions
  	void printWholeBoard(const bool& ascii = true) const;
  	void printBitBoard(const uint64_t& bitboard, const bool& ascii = true) const;
  	void printColorBitBoard(const Color& c, const bool& ascii = true) const;
  	void printPieceBitBoard(const Piece& p, const Color& c, const bool& ascii = true) const;
  	void printBitBoards(const bool& ascii = true) const;
  	
private:
	/* Array of piece bit boards */
	uint64_t m_pieces[NUM_BITBOARDS];

	// gets character for a piece
	char getPieceChar(const Piece& p, const Color& c, const bool& ascii = true) const;
	// prints board array
	void printBoardArray(char board[NUM_RANKS][NUM_FILES], const bool& ascii = true) const;
};

#endif // BOARD_H