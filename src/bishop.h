//
//  bishop.h
//  My Engine
//
//  Created by Nikhil Arora on 9/28/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "constants.h"

/*
We want to perfectly hash the bishop attack based off origin square
and relevant occupancy bits (pieces occupying relevant diagonals)

N - the number of k-bit spaced positions that may be set for 1
(for bishops N <= 8, k = 9 for NoEa diagonals, k = 7 for NoWe diagonals)
arrBishopAttacks: bishop_square -> (table: occ -> attack bitmap)

We mask relevant occupancy squares relative to a bishop placement with
a magic number to get the N relavant bits in the bishops way
We can use this number to hash into the attacks table to get an attack bitboard
*/

/* ---- BISHOP ATTACKS ---- */
// computes magic bishop table for bishop attacks function
void initMagicBishopTable();
uint64_t lookupBishopAttacks(const Square& bishop, const uint64_t& occupancy);
uint64_t calculateBishopAttacks(const Square& bishop, const uint64_t& occupancy);

uint64_t testBishop();

#endif //BISHOP_H