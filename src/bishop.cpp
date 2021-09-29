//
//  bishop.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/28/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "bitops.h"
#include <iostream>


/* ---- MAGIC AND HASHING HELPERS ---- */
Magic magicBishopTable[NUM_SQUARES]; // attacks lookup table with perfect hashing
uint64_t bishopMasks[NUM_SQUARES]; // compute bishop ray masks
uint64_t arrBishopAttacks[NUM_BISHOP_ATTACKS]; // number of bishop attack and occupancy bitmaps
int relevantBits[NUM_SQUARES]; // number of bits from a bishops start to the edge of the board
bool tableInitialized = false; // flag denoting whether attack array was initialized
// computes the bishop masks and number of relevant occupancy bits
void computeBishopMasksAndRelevantBits(){
	for(int i = 0; i < NUM_SQUARES; i++){
		int rank = i / 8;
		int file = i % 8;
		uint64_t bitmask = 0ULL;
		int shifts = 0;
		// north east diagonal
		for(int j = 1; j + rank < NUM_RANKS-1 && j + file < NUM_FILES-1; j++){
			bitmask = setBit(bitmask, i + j * 9);
			shifts++;
		}
		// north west diagonal
		for(int j = 1; j + rank < NUM_RANKS-1 && file - j > 0; j++){
			bitmask = setBit(bitmask, i + j * 7);
			shifts++;
		}
		// south east diagonal
		for(int j = 1; rank - j > 0 && j + file < NUM_FILES-1; j++){
			bitmask = setBit(bitmask, i - j * 7);
			shifts++;
		}
		// south west diagonal
		for(int j = 1; rank - j > 0 && file - j > 0; j++){
			bitmask = setBit(bitmask, i - j * 9);
			shifts++;
		}
		bishopMasks[i] = bitmask;
		relevantBits[i] = shifts;

	}
}
// generate all occupancy permutations
uint64_t* occupancyPermutations(const Square& bishop){
	int rank = (int)bishop / 8;
	int file = (int)bishop % 8;
	int vision = relevantBits[bishop];
	int size = (1 << vision);
	uint64_t* perms = new uint64_t[size];
	if(perms == nullptr){
		std::cerr << "error: unable to allocate memory" << std::endl;
		exit(EXIT_FAILURE);
	}
	perms[0] = 0ULL;
	int index = 1;
	// north east diagonal
	for(int j = 1; j + rank < NUM_RANKS-1 && j + file < NUM_FILES-1; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], bishop + j * 9);
		}
		index *= 2;
	}
	// north west diagonal
	for(int j = 1; j + rank < NUM_RANKS-1 && file - j > 0; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], bishop + j * 7);
		}
		index *= 2;
	}
	// south east diagonal
	for(int j = 1; rank - j > 0 && j + file < NUM_FILES-1; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], bishop - j * 7);
		}
		index *= 2;
	}
	// south west diagonal
	for(int j = 1; rank - j > 0 && file - j > 0; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], bishop - j * 9);
		}
		index *= 2;
	}
	return perms;
}
// generate attacks from bishop and occupancy squares
uint64_t calculateBishopAttacks(const Square& bishop, const uint64_t& occupancy){
	uint64_t attacks = 0ULL;
	int rank = bishop / 8;
	int file = bishop % 8;
	// north east diagonal
	for(int j = 1; j + rank < NUM_RANKS && j + file < NUM_FILES; j++){
		attacks = setBit(attacks, bishop + j * 9);
		if(getBit(occupancy, bishop + j * 9) != 0) 
			break;
	}
	// north west diagonal
	for(int j = 1; j + rank < NUM_RANKS && file - j >= 0; j++){
		attacks = setBit(attacks, bishop + j * 7);
		if(getBit(occupancy, bishop + j * 7) != 0) 
			break;
	}
	// south east diagonal
	for(int j = 1; rank - j >= 0 && j + file < NUM_FILES; j++){
		attacks = setBit(attacks, bishop - j * 7);
		if(getBit(occupancy, bishop - j * 7) != 0) 
			break;
	}
	// south west diagonal
	for(int j = 1; rank - j >= 0 && file - j >= 0; j++){
		attacks = setBit(attacks, bishop - j * 9);
		if(getBit(occupancy, bishop - j * 9) != 0) 
			break;
	}
	return attacks;
}
// fill in the bishop attacks table for fast lookup
void initBishopAttacks(){
	for(int i = 0; i < NUM_SQUARES; i++){
		int vision = relevantBits[i];

		// generate all occupancy permutations
		uint64_t* perms = occupancyPermutations((Square) i);

		// for each occupancy permutation
		// fill in the attacks table for a bishop on square i
		int num_perms = 1 << vision;
		for(int p = 0; p < num_perms; p++){
			uint64_t occ = magicBishopTable[i].mask & perms[p];
			occ *= magicBishopTable[i].magic;
			occ >>= magicBishopTable[i].shift;
			magicBishopTable[i].attacks[occ] = calculateBishopAttacks((Square) i, perms[p]);
		}
		delete[] perms;
	}
}


/* ---- BISHOP ATTACKS ---- */
// computes magic bishop table for bishop attacks function
void initMagicBishopTable(){
	computeBishopMasksAndRelevantBits();
	int attackTableOffset = 0;
	for(int i = 0; i < NUM_SQUARES; i++){
		magicBishopTable[i].attacks = arrBishopAttacks + attackTableOffset;
		magicBishopTable[i].mask = bishopMasks[i];
		magicBishopTable[i].magic = bishopMagicNumbers[i];
		magicBishopTable[i].shift = NUM_SQUARES - relevantBits[i];
		attackTableOffset += (1 << relevantBits[i]);
	}
	initBishopAttacks();
	tableInitialized = true;
}
// performs a lookup into the pre-initialized bishop attack table
uint64_t lookupBishopAttacks(const Square& bishop, const uint64_t& occupancy){
	if(tableInitialized){
		if(bishop == none){
			std::cerr << "None square provided to bishop attacks lookup" << std::endl;
			return 0;
		}
		uint64_t occ = occupancy;
		occ &= magicBishopTable[bishop].mask;
		occ *= magicBishopTable[bishop].magic;
		occ >>= magicBishopTable[bishop].shift;
		return magicBishopTable[bishop].attacks[occ];
	}
	else{
		//error
		std::cerr << "Error: attempted to access bishop attacks array before array initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}


uint64_t testBishop(){
	initMagicBishopTable();
	return 0ULL;//calculateBishopAttacks(a1, setBit(0ULL, (int)h8));
}