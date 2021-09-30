//
//  knight.h
//  My Engine
//
//  Created by Nikhil Arora on 9/27/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

/*
Compass rose for knight movement:
        noNoWe    noNoEa
            +15  +17
             |     |
noWeWe  +6 __|     |__+10  noEaEa
              \   /
               >0<
           __ /   \ __
soWeWe -10   |     |   -6  soEaEa
             |     |
            -17  -15
        soSoWe    soSoEa

*/
#ifndef KNIGHT_H
#define KNIGHT_H

#include "constants.h"

/* ---- KNIGHT PATTERN ---- */
// initialize pre-calculated knight attacks
void computeKnightAttacks();
// get knight attacks by origin square
uint64_t lookupKnightAttacks(Square knight);
// attacks of multiple knights on one bitboard
uint64_t knightAttacks(const uint64_t& knights);
// fill cycle for knights (can be re-applied n times to get all knight-reachable squares within n moves)
uint64_t knightFill(const uint64_t& knights);
// target squares of all knight forks
uint64_t forkTargetSquare(const uint64_t& targets);

#endif //KNIGHT_H