//
//  board.h
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

Bitboard is indexed little-endian rank-file wise:
h8...b2a2h1...c1b1a1

m_side: side to move (white or black)

m_castle_ability: array of castling position booleans

m_en_passant_target: square that can be targeted thru en passant (-1 if none exists)

m_half_moves: number of half moves (w.r.t. 50 move rule), reset on pawn move or capture

m_num_moves: number of moves in the game, increments after black moves

*/

#include <cstdint>
#include "constants.h"
#include "bitops.h"
#include <string>
#include "fen.h"

/* Board class: collection of bit boards for each piece */

class Board{
public:
	// builds a board at the starting position
	Board();
	// builds a board using given bit boards
	Board(uint64_t pieces[NUM_BITBOARDS], Color side, 
	      bool castle_ability[4], Square en_passant_target, 
	      int half_moves, int num_moves);
	// copy constructor
	Board(const Board& other);
	// constructs board from FEN strings
	Board(const std::string& FEN);

  	// functions that get the piece bit boards
  	uint64_t getPieceBitBoard(const Piece& p, const Color& c) const;
  	uint64_t getAllPieces() const;
  	uint64_t getEmptySquares() const;
  	uint64_t getAllColorPieces(const Color& c) const;
  	uint64_t getPawns(const Color& c) const;
  	uint64_t getKnights(const Color& c) const;
  	uint64_t getBishops(const Color& c) const;
  	uint64_t getRooks(const Color& c) const;
  	uint64_t getQueen(const Color& c) const;
  	uint64_t getKing(const Color& c) const;

  	// other getters
  	Color getSideToMove() const;
  	bool getCastleAbility(const int& castle_side) const;
  	Square getEnPassantTarget() const;
  	int getHalfMoves() const;
  	int getNumMoves() const;

  	// print functions
  	void printBoard() const;
  	void printBoard(const uint64_t& b) const;
  	void printColorBitBoard(const Color& c) const;
  	void printPieceBitBoard(const Piece& p, const Color& c) const;
  	void printAllBitBoards() const;
  	
private:
	/* Array of piece bit boards */
	uint64_t m_pieces[NUM_BITBOARDS];
	/* Side to move */
	Color m_side;
	/* Castling ability */
	bool m_castle_ability[4];
	/* En Passant Target Square */
	Square m_en_passant_target;
	/* Half Move Clock */
	int m_half_moves;
	/* Full Move Counter */
	int m_num_moves;


	// gets character for a piece
	char getPieceChar(const Piece& p, const Color& c) const;
	// prints board array
	void printBoardArray(char board[NUM_RANKS][NUM_FILES]) const;
};

#endif // BOARD_H