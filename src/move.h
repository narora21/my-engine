//
//  move.h
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//


/*
Move encoding:
{flags, from, to} -> 16 bits
6 bits for "to" square
6 bits for "from" square
4 bits for flags (promotion, capture, move type):
code	promotion:	capture:	special1:	special0:	kind of move:
0			0			0			0			0		quiet moves
1			0			0			0			1		double pawn push
2			0			0			1			0		kingside castle
3			0			0			1			1		queenside castle
4			0			1			0			0		captures
5			0			1			0			1		ep-capture
8			1			0			0			0		knight-promotion
9			1			0			0			1		bishop-promotion
10			1			0			1			0		rook-promotion
11			1			0			1			1		queen-promotion
12			1			1			0			0		knight-promo capture
13			1			1			0			1		bishop-promo capture
14			1			1			1			0		rook-promo capture
15			1			1			1			1		queen-promo capture

*/

#ifndef MOVE_H
#define MOVE_H

#include "constants.h"

class Move{
public:
	Move(unsigned int to, unsigned int from, unsigned int flags);

	// operators
	void operator=(Move rval);
	bool operator==(Move rval) const;
	bool operator!=(Move rval) const;

	// getters
	unsigned int getToSquare() const;
	unsigned int getFromSquare() const;
	unsigned int getFlags() const;

	// setters
	void setToSquare(unsigned int to);
	void setFrom(unsigned int from);
	void setFlags(unsigned int flags);

	// decode flag meaning
	bool isCapture() const;
	bool isPromotion() const;
	bool isDoublePawnPush() const;
	bool isCastle() const;
	bool isKingSideCastle() const;
	bool isQueenSideCastle() const;
	bool isEnPassant() const;
	Piece promotionType() const;

private:
	unsigned int m_move;
};

#endif //MOVE_H