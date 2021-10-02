//
//  rook.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/28/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "rook.h"
#include "bitops.h"
#include <iostream>


/* ---- MAGIC AND HASHING HELPERS ---- */
Magic magicRookTable[NUM_SQUARES]; // attacks lookup table with perfect hashing
uint64_t rookMasks[NUM_SQUARES]; // compute rook ray masks
uint64_t arrRookAttacks[NUM_ROOK_ATTACKS]; // number of rook attack and occupancy bitmaps
int relevantRookBits[NUM_SQUARES]; // number of bits from a rooks start to the edge of the board
bool rookTableInitialized = false; // flag denoting whether attack array was initialized
// computes the rook masks and number of relevant occupancy bits
void computeRookMasksAndRelevantBits(){
	for(int i = 0; i < NUM_SQUARES; i++){
		int rank = i / 8;
		int file = i % 8;
		uint64_t bitmask = 0ULL;
		int shifts = 0;
		// north
		for(int j = 1; j + rank < NUM_RANKS-1; j++){
			bitmask = setBit(bitmask, i + j * 8);
			shifts++;
		}
		// south
		for(int j = 1; rank - j > 0; j++){
			bitmask = setBit(bitmask, i - j * 8);
			shifts++;
		}
		// east
		for(int j = 1; j + file < NUM_FILES-1; j++){
			bitmask = setBit(bitmask, i + j);
			shifts++;
		}
		// west
		for(int j = 1; file - j > 0; j++){
			bitmask = setBit(bitmask, i - j);
			shifts++;
		}
		rookMasks[i] = bitmask;
		relevantRookBits[i] = shifts;

	}
}
// generate all occupancy permutations
uint64_t* occupancyRookPermutations(Square rook){
	int rank = (int)rook / 8;
	int file = (int)rook % 8;
	int vision = relevantRookBits[rook];
	int size = (1 << vision);
	uint64_t* perms = new uint64_t[size];
	if(perms == nullptr){
		std::cerr << "error: unable to allocate memory" << std::endl;
		exit(EXIT_FAILURE);
	}
	perms[0] = 0ULL;
	int index = 1;
	// north 
	for(int j = 1; j + rank < NUM_RANKS-1; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], rook + j * 8);
		}
		index *= 2;
	}
	// south
	for(int j = 1; rank - j > 0; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], rook - j * 8);
		}
		index *= 2;
	}
	// east
	for(int j = 1; j + file < NUM_FILES-1; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], rook + j);
		}
		index *= 2;
	}
	// west
	for(int j = 1; file - j > 0; j++){
		for(int i = 0; i < index; i++){
			perms[index + i] = setBit(perms[i], rook - j);
		}
		index *= 2;
	}
	return perms;
}
// generate attacks from rook and occupancy squares
uint64_t calculateRookAttacks(Square rook, uint64_t occupancy){
	uint64_t attacks = 0ULL;
	int rank = rook / 8;
	int file = rook % 8;
	// north
	for(int j = 1; j + rank < NUM_RANKS; j++){
		attacks = setBit(attacks, rook + j * 8);
		if(getBit(occupancy, rook + j * 8) != 0) 
			break;
	}
	// south
	for(int j = 1; rank - j >= 0; j++){
		attacks = setBit(attacks, rook - j * 8);
		if(getBit(occupancy, rook - j * 8) != 0) 
			break;
	}
	// east
	for(int j = 1; j + file < NUM_FILES; j++){
		attacks = setBit(attacks, rook + j);
		if(getBit(occupancy, rook + j) != 0) 
			break;
	}
	// west
	for(int j = 1; file - j >= 0; j++){
		attacks = setBit(attacks, rook - j);
		if(getBit(occupancy, rook - j) != 0) 
			break;
	}
	return attacks;
}
// fill in the rook attacks table for fast lookup
void initRookAttacks(){
	for(int i = 0; i < NUM_SQUARES; i++){
		int vision = relevantRookBits[i];

		// generate all occupancy permutations
		uint64_t* perms = occupancyRookPermutations((Square) i);

		// for each occupancy permutation
		// fill in the attacks table for a rook on square i
		int num_perms = 1 << vision;
		for(int p = 0; p < num_perms; p++){
			uint64_t occ = magicRookTable[i].mask & perms[p];
			occ *= magicRookTable[i].magic;
			occ >>= magicRookTable[i].shift;
			magicRookTable[i].attacks[occ] = calculateRookAttacks((Square) i, perms[p]);
		}
		delete[] perms;
	}
}


/* ---- ROOK ATTACKS ---- */
// computes magic rook table for rook attacks function
void initMagicRookTable(){
	computeRookMasksAndRelevantBits();
	int attackTableOffset = 0;
	for(int i = 0; i < NUM_SQUARES; i++){
		magicRookTable[i].attacks = arrRookAttacks + attackTableOffset;
		magicRookTable[i].mask = rookMasks[i];
		magicRookTable[i].magic = rookMagicNumbers[i];
		magicRookTable[i].shift = NUM_SQUARES - relevantRookBits[i];
		attackTableOffset += (1 << relevantRookBits[i]);
	}
	initRookAttacks();
	rookTableInitialized = true;
}
// performs a lookup into the pre-initialized rook attack table
uint64_t lookupRookAttacks(Square rook, uint64_t occupancy){
	if(rookTableInitialized){
		if(rook == noneSquare){
			std::cerr << "None square provided to rook attacks lookup" << std::endl;
			return 0;
		}
		uint64_t occ = occupancy;
		occ &= magicRookTable[rook].mask;
		occ *= magicRookTable[rook].magic;
		occ >>= magicRookTable[rook].shift;
		return magicRookTable[rook].attacks[occ];
	}
	else{
		//error
		std::cerr << "Error: attempted to access rook attacks array before array initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}


