//
//  king.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/27/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "king.h"
#include "bitops.h"
#include <iostream>

uint64_t arrKingAttacks[NUM_SQUARES];
bool arrKingAttacksInitialized = false;
// computes king attacks array
void computeKingAttacks(){
	if(!arrKingAttacksInitialized){
		for(int i = 0; i < NUM_SQUARES; i++){
			uint64_t king = 1ULL;
			king = king << i;
			arrKingAttacks[i] = kingAttacks(king);
		}
		arrKingAttacksInitialized = true;
	}
}
// get king attacks by origin square from pre-initialized array
uint64_t lookupKingAttacks(Square king){
	if(arrKingAttacksInitialized){
		if(king == none){
			std::cerr << "None square provided to king attacks lookup" << std::endl;
			return 0;
		}
		return arrKingAttacks[king];
	}
	else{
		//error
		std::cerr << "Error: attempted to access king attacks array before array initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}
// calculates king attacks
uint64_t kingAttacks(const uint64_t& king){
	uint64_t attacks = eastOne(king) | westOne(king);
	attacks |= northOne(attacks) | southOne(attacks);
	attacks |= northOne(king) | southOne(king);
	return attacks;
}