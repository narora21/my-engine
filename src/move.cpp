//
//  move.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "move.h"
#include <iostream>
#include "board.h"

/* ---- MOVE CONSTRUCTOR ---- */
Move::Move(unsigned int to, unsigned int from, unsigned int flags){
	//move =      4 flag bits 			  6 from bits		 6 to bits
	m_move = ((flags & 0x0F) << 12) | ((from & 0x3F) << 6) | (to & 0x3F);
}

/* ---- OPERATORS ---- */
void Move::operator=(Move rval){
	m_move = rval.m_move;
}
bool Move::operator==(Move rval) const{
	return m_move == rval.m_move;
}
bool Move::operator!=(Move rval) const{
	return m_move != rval.m_move;
}
Move::operator std::string() const{
	return squareToString(getFromSquare()) + squareToString(getToSquare());
}

/* ---- GETTERS ---- */
unsigned int Move::getToSquare() const{
	return m_move & 0x3F;
}
unsigned int Move::getFromSquare() const{
	return (m_move >> 6) & 0X3F;
}
unsigned int Move::getFlags() const{
	return (m_move >> 12) & 0x0F;
}

/* ---- SETTERS ---- */
void Move::setToSquare(unsigned int to){
	m_move &= 0xFFC0;
	m_move |= (to & 0x3F);
}
void Move::setFrom(unsigned int from){
	m_move &= 0xF03F;
	m_move |= ((from & 0x3F) << 6);
}
void Move::setFlags(unsigned int flags){
	m_move &= 0x0FFF;
	m_move |= ((flags & 0x0F) << 12);
}

/* ---- DECODE FLAGS ---- */
bool Move::isCapture() const{
	return (m_move & 0x4000) != 0;
}
bool Move::isPromotion() const{
	return (m_move & 0X8000) != 0;
}
bool Move::isDoublePawnPush() const{
	return (m_move & 0xF000) == 0x1000;
}
bool Move::isCastle() const{
	return ((m_move & 0xF000) == 0x2000) || ((m_move & 0xF000) == 0x3000);
}
bool Move::isKingSideCastle() const{
	return (m_move & 0xF000) == 0x2000;
}
bool Move::isQueenSideCastle() const{
	return (m_move & 0xF000) == 0x3000;
}
bool Move::isEnPassant() const{
	return (m_move & 0xF000) == 0x5000;
}
Piece Move::promotionType() const{
	unsigned int code = (m_move >> 12) & 0x03;
	switch(code){
		case 0: return nKnight; break;
		case 1: return nBishop; break;
		case 2: return nRook; break;
		case 3: return nQueen; break;
	}
	return nAll;
}

/* ---- LEGALITY TESTS ---- */
uint64_t arrInBetweens[64*65/2];
bool inBetweensInitialized = false;
// in between code from: https://www.chessprogramming.org/Square_Attacked_By
uint64_t inBetweenCalc(Square sq1, Square sq2) {
   const uint64_t m1   = 0xFFFFFFFFFFFFFFFFULL;
   const uint64_t a2a7 = 0x0001010101010100ULL;
   const uint64_t b2g7 = 0x0040201008040200ULL;
   const uint64_t h1b7 = 0x0002040810204080ULL;
   uint64_t btwn, line, rank, file;

   btwn  = (m1 << sq1) ^ (m1 << sq2);
   file  =   (sq2 & 7) - (sq1   & 7);
   rank  =  ((sq2 | 7) -  sq1) >> 3 ;
   line  =      (   (file  &  7) - 1) & a2a7; /* a2a7 if same file */
   line += 2 * ((   (rank  &  7) - 1) >> 58); /* b1g1 if same rank */
   line += (((rank - file) & 15) - 1) & b2g7; /* b2g7 if same diagonal */
   line += (((rank + file) & 15) - 1) & h1b7; /* h1b7 if same antidiag */
   line *= btwn & -btwn; /* mul acts like shift by smaller square */
   return line & btwn;   /* return the bits on that line in-between */
}
int triangularIndex(int a, int b) {
   int d = a - b; /* difference */
   d &= d >> 31;  /* only if negative */
   b += d;        /* min */
   a -= d;        /* max */
   b *= b ^ 127;  /* min * (127-min)  ... */
   return (b>>1) + a; /* ... /2 + max */
}
void initInBetweens(){
	for(int from = 0; from < NUM_SQUARES; from++){
		for(int to = 0; to < NUM_SQUARES; to++){
			arrInBetweens[triangularIndex(from, to)] = inBetweenCalc((Square)from, (Square)to);
		}
	}
	inBetweensInitialized = true;
}

// bitmask of all squares on a diagonal or straight path (exclusive)
uint64_t inBetween(Square from, Square to){
	if(inBetweensInitialized){
		return arrInBetweens[triangularIndex(from, to)];
	}
	else{
		//error
		std::cerr << "Error: attempted to access in betweens array before array initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}