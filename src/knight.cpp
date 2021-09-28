//
//  knight.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/27/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "knight.h"
#include "bitops.h"
#include <iostream>


/* ---- KNIGHT PATTERN ---- */
uint64_t arrKnightAttacks[NUM_SQUARES];
bool arrKnightAttacksInitialized = false;
// computes knight attacks array
void computeKnightAttacks(){
	if(!arrKnightAttacksInitialized){
		for(int i = 0; i < NUM_SQUARES; i++){
			uint64_t knight = 1;
			knight = knight << i;
			arrKnightAttacks[i] = knightAttacks(knight);
		}
		arrKnightAttacksInitialized = true;
	}
}
// get knight attacks by origin square from pre-initialized array
uint64_t lookupKnightAttacks(const Square& knight){
	if(arrKnightAttacksInitialized){
		if(knight == none){
			std::cerr << "None square provided to knight attacks lookup" << std::endl;
			return 0;
		}
		return arrKnightAttacks[knight];
	}
	else{
		//error
		std::cerr << "Error: attempted to access knight attacks array before array initialization" << std::endl;
		exit(EXIT_FAILURE);
	}
}
// calculates attacks of multiple knights bitboard
uint64_t knightAttacks(const uint64_t& knights){
	uint64_t l1 = (knights >> 1) & NOT_H_FILE;
   	uint64_t l2 = (knights >> 2) & NOT_GH_FILES;
   	uint64_t r1 = (knights << 1) & NOT_A_FILE;
   	uint64_t r2 = (knights << 2) & NOT_AB_FILES;
   	uint64_t h1 = l1 | r1;
   	uint64_t h2 = l2 | r2;
   	return (h1 << 16) | (h1 >> 16) | (h2 << 8) | (h2 >> 8);
}
// fill cycle for knights (can be re-applied n times to get all knight-reachable squares within n moves)
uint64_t knightFill(const uint64_t& knights) {
	return knightAttacks(knights) | knights;
}
// target squares of all knight forks
uint64_t forkTargetSquare(const uint64_t& targets) {
   uint64_t west, east, attacks, forks;
   east   = eastOne (targets);
   west   = westOne (targets);
   attacks  =  east << 16;
   forks  = (west << 16) & attacks;
   attacks |=  west << 16;
   forks |= (east >> 16) & attacks;
   attacks |=  east >> 16;
   forks |= (west >> 16) & attacks;
   attacks |=  west >> 16;
   east   = eastOne (east);
   west   = westOne (west);
   forks |= (east <<  8) & attacks;
   attacks |=  east <<  8;
   forks |= (west <<  8) & attacks;
   attacks |=  west <<  8;
   forks |= (east >>  8) & attacks;
   attacks |=  east >>  8;
   forks |= (west >>  8) & attacks;
   return forks;
}

