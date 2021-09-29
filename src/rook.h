//
//  rook.h
//  My Engine
//
//  Created by Nikhil Arora on 9/28/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef ROOK_H
#define ROOK_H

#include "constants.h"
#include <cstdint>

/*
We want to perfectly hash the Rook attack based off origin square
and relevant occupancy bits (pieces occupying relevant diagonals)

N - the number of k-bit spaced positions that may be set for 1
(for rooks N = k = 8)
arrRookAttacks: rook_square -> (table: occ -> attack bitmap)

We mask relevant occupancy squares, relative to a rook placement, with
a magic number to get the N relavant bits in the rooks way
We can use this number to hash into the attacks table to get an attack bitboard
*/

/* ---- ROOK ATTACKS ---- */
// computes magic rook table for rook attacks function
void initMagicRookTable();
// performs lookup into pre-initialized rook attack table
uint64_t lookupRookAttacks(const Square& rook, const uint64_t& occupancy);
// calculates rook attack bitmap
uint64_t calculateRookAttacks(const Square& rook, const uint64_t& occupancy);


#endif //ROOK_H