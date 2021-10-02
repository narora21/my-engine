//
//  unittests.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/24/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "unittests.h"

/* ---- BITBOARD TESTS ---- */

/* ---- PAWN TESTS ---- */

/* ---- HELPER FUNCTIONS ---- */
std::string squareToString(unsigned int s){
	unsigned int rank = s / 8;
	unsigned int file = s % 8;
	std::string ret = "";
	ret.push_back('a' + file);
	ret.push_back('1' + rank);
	return ret;
}
unsigned int stringToSquare(std::string s){
	unsigned int file = s[0] - 'a';
	unsigned int rank = s[1] - '1';
	return file + 8*rank;
}