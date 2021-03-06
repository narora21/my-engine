//
//  bitops.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/23/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "bitops.h"
#include "constants.h"
#include <stdlib.h>
#include <iostream>


/* ---- MOVE ONE STEP ---- */
uint64_t southOne(uint64_t b) {return b >> 8;}
uint64_t northOne(uint64_t b) {return b << 8;}
uint64_t eastOne(uint64_t b) {return (b << 1) & NOT_A_FILE;}
uint64_t noEaOne(uint64_t b) {return (b << 9) & NOT_A_FILE;}
uint64_t soEaOne(uint64_t b) {return (b >> 7) & NOT_A_FILE;}
uint64_t westOne(uint64_t b) {return (b >> 1) & NOT_H_FILE;}
uint64_t noWeOne(uint64_t b) {return (b << 7) & NOT_H_FILE;}
uint64_t soWeOne(uint64_t b) {return (b >> 9) & NOT_H_FILE;}

/* ---- KNIGHT STEPS ---- */
uint64_t noNoEa(uint64_t b) {return (b << 17) & NOT_A_FILE;}
uint64_t noEaEa(uint64_t b) {return (b << 10) & NOT_AB_FILES;}
uint64_t soEaEa(uint64_t b) {return (b >>  6) & NOT_AB_FILES;}
uint64_t soSoEa(uint64_t b) {return (b >> 15) & NOT_A_FILE;}
uint64_t noNoWe(uint64_t b) {return (b << 15) & NOT_H_FILE;}
uint64_t noWeWe(uint64_t b) {return (b <<  6) & NOT_GH_FILES;}
uint64_t soWeWe(uint64_t b) {return (b >> 10) & NOT_GH_FILES;}
uint64_t soSoWe(uint64_t b) {return (b >> 17) & NOT_H_FILE;}

/* ---- ROTATE FUNCTIONS ---- */
//uint64_t rotateLeft (uint64_t b, int s) {return _rotl64(b, s);}
//uint64_t rotateRight(uint64_t b, int s) {return _rotr64(b, s);}

/* ---- BITWISE OPS ---- */

// Get population count of bitboard
int populationCount(uint64_t b){
	return __builtin_popcountll(b);
}
// Check if population is 1
bool popCountIsOne(uint64_t b){
	return (b != 0ULL && (b & (b-1ULL)) == 0ULL);
}
// Check if population is less than or equal to 1
bool popCountLseOne(uint64_t b){
	return ((b & (b-1ULL)) == 0ULL);
}
// Check if population is more than 1
int popCountGtOne(uint64_t b){
	return (b & (b-1ULL)); // pop is gt 1 if this is != 0
}
// Index of least significant 1 bit, -1 if b == 0
int getLS1bIndex(uint64_t b){
	return __builtin_ffsll(b)-1ULL;
}
// Resets least significant 1 bit
uint64_t clearLS1b(uint64_t b){
	return b & (b-1ULL);
}
// Toggles nth bit
uint64_t toggleBit(uint64_t b, int n){
	uint64_t bitmask = (1ULL << n);
	return b ^ bitmask;
}
// Sets nth bit
uint64_t setBit(uint64_t b, int n){
	uint64_t bitmask = (1ULL << n);
	return b | bitmask;
}
// Clears nth bit
uint64_t clearBit(uint64_t b, int n){
	uint64_t bitmask = ~(1ULL << n);
	return b & bitmask;
}
// Gets nth bit
uint64_t getBit(uint64_t b, int n){
	uint64_t bitmask = (1ULL << n);
	return b & bitmask;
}

/* ---- PRINT FUNCTIONS ---- */
void printBitBoard(uint64_t b){
	for(int i = NUM_RANKS - 1; i >= 0; i--){
		for(int j = 0; j < NUM_FILES; j++){
			int shift = i*NUM_RANKS + j;
			std::cout << ((b >> shift) & 1);
		}
		std::cout << std::endl;
	}
}