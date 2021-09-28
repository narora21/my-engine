//
//  constants.h
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

/* ---- TYPE DECLARATIONS ---- */
typedef uint64_t BitBoard;

/* ---- ENUMS ---- */
/* Enum aliases for colors, pieces, and squares */
enum Color{
	nWhite,
	nBlack
};
enum Piece{
	nAll,
  nPawn,
  nKnight,
  nBishop,
  nRook,
  nQueen,
  nKing
};
enum Square {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8,
  none = -1
};


/* ---- BOARD CONSTANTS ---- */

#define NUM_BITBOARDS 14
#define NUM_SQUARES 64
#define NUM_FILES 8
#define NUM_RANKS 8
#define NUM_COLORS 2
#define UNIVERSE 0xFFFFFFFFFFFFFFFFULL
#define EMPTY 0x0000000000000000ULL

// file constants
#define A_FILE 0x0101010101010101ULL
#define B_FILE 0x0202020202020202ULL
#define C_FILE 0x0404040404040404ULL
#define D_FILE 0x0808080808080808ULL
#define E_FILE 0x1010101010101010ULL
#define F_FILE 0x2020202020202020ULL
#define G_FILE 0x4040404040404040ULL
#define H_FILE 0x8080808080808080ULL

#define NOT_A_FILE 0xFEFEFEFEFEFEFEFEULL
#define NOT_H_FILE 0X7F7F7F7F7F7F7F7FULL
#define NOT_AB_FILES 0xFCFCFCFCFCFCFCFCULL
#define NOT_GH_FILES 0x3F3F3F3F3F3F3F3FULL
#define ABC_FILES 0x0707070707070707ULL
#define FGH_FILES 0xE0E0E0E0E0E0E0E0ULL
#define BCD_FILES 0x0E0E0E0E0E0E0E0EULL
#define EFG_FILES 0x7070707070707070ULL

// rank constants
#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_3 0x0000000000FF0000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL

#define NOT_RANK_8 0x00FFFFFFFFFFFFFFULL
#define NOT_RANK_1 0xFFFFFFFFFFFFFF00ULL

// diagonal constants
#define a1h8_DIAGONAL 0x8040201008040201ULL
#define h1a8_DIAGONAL 0x0102040810204080ULL

// light and dark square constants
#define LIGHT_SQUARES 0x55AA55AA55AA55AAULL
#define DARK_SQUARES 0xAA55AA55AA55AA55ULL


/* ---- PIECE CONSTANTS ---- */

// White pieces
#define WHITE_PIECES_START 0x000000000000FFFFULL
#define WHITE_PAWN_START 0x000000000000FF00ULL
#define WHITE_KNIGHT_START 0x0000000000000042ULL
#define WHITE_BISHOP_START 0x0000000000000024ULL
#define WHITE_ROOK_START 0x0000000000000081ULL
#define WHITE_QUEEN_START 0x0000000000000008ULL
#define WHITE_KING_START 0x0000000000000010ULL

// Black Pieces
#define BLACK_PIECES_START 0xFFFF000000000000ULL
#define BLACK_PAWN_START 0x00FF000000000000ULL
#define BLACK_KNIGHT_START 0x4200000000000000ULL
#define BLACK_BISHOP_START 0x2400000000000000ULL
#define BLACK_ROOK_START 0x8100000000000000ULL
#define BLACK_QUEEN_START 0x0800000000000000ULL
#define BLACK_KING_START 0x1000000000000000ULL

/* ---- CASTLING ABILITY CONSTANTS ---- */
#define WHITE_KING_SIDE_CASTLE 0
#define WHITE_QUEEN_SIDE_CASTLE 1
#define BLACK_KING_SIDE_CASTLE 2
#define BLACK_QUEEN_SIDE_CASTLE 3


/* ---- CHARACTER CONSTANTS ---- */
// White Pieces
#define WhitePawnChar '\u2659'
#define WhiteKnightChar '\u2658'
#define WhiteBishopChar '\u2657'
#define WhiteRookChar '\u2656'
#define WhiteQueenChar '\u2655'
#define WhiteKingChar '\u2654'
// Black Pieces
#define BlackPawnChar '\u265F'
#define BlackKnightChar '\u265E'
#define BlackBishopChar '\u265D'
#define BlackRookChar '\u265C'
#define BlackQueenChar '\u265B'
#define BlackKingChar '\u265A'


#endif //CONSTANTS_H