//
//  king.h
//  My Engine
//
//  Created by Nikhil Arora on 9/27/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef KING_H
#define KING_H

#include "constants.h"

/* ---- KING ATTACKS ---- */
// computes the array of king attacks
void initKingAttacks();
// lookup king attacks from pre-initialized array
uint64_t lookupKingAttacks(Square king);
// calculate king attacks
uint64_t kingAttacks(uint64_t king);

#endif //KING_H