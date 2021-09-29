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
#include <string>

/*
Board defintion: little-endian rank-file mapping
  noWe         nort         noEa
          +7    +8    +9
              \  |  /
  west    -1 <-  0 -> +1    east
              /  |  \
          -9    -8    -7
  soWe         sout         soEa
*/

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

/* ---- MATERIAL POINT VALUES ---- */
#define PAWN_VALUE 1
#define KNIGHT_VALUE 3
#define BISHOP_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9

/* ---- PIECE CHARACTERS ---- */
#define EMPTY_CHAR ' '
#define WHITE_PAWN_CHAR 'P'
#define WHITE_KNIGHT_CHAR 'N'
#define WHITE_BISHOP_CHAR 'B'
#define WHITE_ROOK_CHAR 'R'
#define WHITE_QUEEN_CHAR 'Q'
#define WHITE_KING_CHAR 'K'
#define BLACK_PAWN_CHAR 'p'
#define BLACK_KNIGHT_CHAR 'n'
#define BLACK_BISHOP_CHAR 'b'
#define BLACK_ROOK_CHAR 'r'
#define BLACK_QUEEN_CHAR 'q'
#define BLACK_KING_CHAR 'k'


/* ---- MAGIC NUMBERS ---- */
typedef struct{
  uint64_t* attacks; // pointer to attack_table for each particular square
  uint64_t mask; // to mask relevant squares of both lines (no outer squares)
  uint64_t magic; // magic 64-bit factor
  int shift; // shift right value
} Magic;

// size of bishop attacks array = SUM(2^(n_i)) 
// where n_i = # of relevant occupancy squares relative to a bishop on square i (0 <= i <= 63)
// this number is strictly greater than the true number of bishop attacks
#define NUM_BISHOP_ATTACKS 5248
// size of rook attacks array = SUM(2^(n_i)) 
// where n_i = # of relevant occupancy squares relative to a rook on square i (0 <= i <= 63)
// this number is strictly greater than the true number of rook attacks
#define NUM_ROOK_ATTACKS 102400

// https://www.chessprogramming.org/Best_Magics_so_far
const uint64_t rookMagicNumbers[64] = {
  0x11800040001481a0ULL,
  0x2040400010002000ULL,
  0xa280200308801000ULL,
  0x100082005021000ULL,
  0x280280080040006ULL,
  0x200080104100200ULL,
  0xc00040221100088ULL,
  0xe00072200408c01ULL,
  0x2002045008600ULL,
  0xa410804000200089ULL,
  0x4081002000401102ULL,
  0x2000c20420010ULL,
  0x800800400080080ULL,
  0x40060010041a0009ULL,
  0x441004442000100ULL,
  0x462800080004900ULL,
  0x80004020004001ULL,
  0x1840420021021081ULL,
  0x8020004010004800ULL,
  0x940220008420010ULL,
  0x2210808008000400ULL,
  0x24808002000400ULL,
  0x803604001019a802ULL,
  0x520000440081ULL,
  0x802080004000ULL,
  0x1200810500400024ULL,
  0x8000100080802000ULL,
  0x2008080080100480ULL,
  0x8000404002040ULL,
  0xc012040801104020ULL,
  0xc015000900240200ULL,
  0x20040200208041ULL,
  0x1080004000802080ULL,
  0x400081002110ULL,
  0x30002000808010ULL,
  0x2000100080800800ULL,
  0x2c0800400800800ULL,
  0x1004800400800200ULL,
  0x818804000210ULL,
  0x340082000a45ULL,
  0x8520400020818000ULL,
  0x2008900460020ULL,
  0x100020008080ULL,
  0x601001000a30009ULL,
  0xc001000408010010ULL,
  0x2040002008080ULL,
  0x11008218018c0030ULL,
  0x20c0080620011ULL,
  0x400080002080ULL,
  0x8810040002500ULL,
  0x400801000200080ULL,
  0x2402801000080480ULL,
  0x204040280080080ULL,
  0x31044090200801ULL,
  0x40c10830020400ULL,
  0x442800100004080ULL,
  0x10080002d005041ULL,
  0x134302820010a2c2ULL,
  0x6202001080200842ULL,
  0x1820041000210009ULL,
  0x1002001008210402ULL,
  0x2000108100402ULL,
  0x10310090a00b824ULL,
  0x800040100944822ULL,
};



const uint64_t bishopMagicNumbers[64] = {
    0xc085080200420200ULL,
    0x60014902028010ULL,
    0x401240100c201ULL,
    0x580ca104020080ULL,
    0x8434052000230010ULL,
    0x102080208820420ULL,
    0x2188410410403024ULL,
    0x40120805282800ULL,
    0x4420410888208083ULL,
    0x1049494040560ULL,
    0x6090100400842200ULL,
    0x1000090405002001ULL,
    0x48044030808c409ULL,
    0x20802080384ULL,
    0x2012008401084008ULL,
    0x9741088200826030ULL,
    0x822000400204c100ULL,
    0x14806004248220ULL,
    0x30200101020090ULL,
    0x148150082004004ULL,
    0x6020402112104ULL,
    0x4001000290080d22ULL,
    0x2029100900400ULL,
    0x804203145080880ULL,
    0x60a10048020440ULL,
    0xc08080b20028081ULL,
    0x1009001420c0410ULL,
    0x101004004040002ULL,
    0x1004405014000ULL,
    0x10029a0021005200ULL,
    0x4002308000480800ULL,
    0x301025015004800ULL,
    0x2402304004108200ULL,
    0x480110c802220800ULL,
    0x2004482801300741ULL,
    0x400400820a60200ULL,
    0x410040040040ULL,
    0x2828080020011000ULL,
    0x4008020050040110ULL,
    0x8202022026220089ULL,
    0x204092050200808ULL,
    0x404010802400812ULL,
    0x422002088009040ULL,
    0x180604202002020ULL,
    0x400109008200ULL,
    0x2420042000104ULL,
    0x40902089c008208ULL,
    0x4001021400420100ULL,
    0x484410082009ULL,
    0x2002051108125200ULL,
    0x22e4044108050ULL,
    0x800020880042ULL,
    0xb2020010021204a4ULL,
    0x2442100200802dULL,
    0x10100401c4040000ULL,
    0x2004a48200c828ULL,
    0x9090082014000ULL,
    0x800008088011040ULL,
    0x4000000a0900b808ULL,
    0x900420000420208ULL,
    0x4040104104ULL,
    0x120208c190820080ULL,
    0x4000102042040840ULL,
    0x8002421001010100ULL,
};


#endif //CONSTANTS_H