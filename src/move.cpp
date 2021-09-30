//
//  move.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "move.h"

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