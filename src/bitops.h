//
//  bitops.h
//  My Engine
//
//  Created by Nikhil Arora on 9/23/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

/*
uint64_t functions that manipulate the uint64_t bitboards
The bit boards use a little-endian rank-file mapping 
Movement is defined by the following compass rose:
  noWe         nort         noEa
          +7    +8    +9
              \  |  /
  west    -1 <-  0 -> +1    east
              /  |  \
          -9    -8    -7
  soWe         sout         soEa
*/

#ifndef BITOPS_H
#define BITOPS_H

#include "constants.h"
#include <cstdint>
#include <stdlib.h>

/* ---- MOVE ONE STEP ---- */
uint64_t southOne(const uint64_t& b);
uint64_t northOne(const uint64_t& b);
uint64_t eastOne(const uint64_t& b);
uint64_t noEaOne(const uint64_t& b);
uint64_t soEaOne(const uint64_t& b);
uint64_t westOne(const uint64_t& b);
uint64_t noWeOne(const uint64_t& b);
uint64_t soWeOne(const uint64_t& b);

/* ---- ROTATE FUNCTIONS ---- */
//uint64_t rotateLeft (uint64_t b, int s);
//uint64_t rotateRight(uint64_t b, int s);

/* ---- BITWISE OPS ---- */
int populationCount(uint64_t b);
bool popCountIsOne(uint64_t b);
bool popCountLseOne(uint64_t b);
int popCountGtOne(uint64_t b);
int getLS1bIndex(uint64_t b);
uint64_t clearLS1b(uint64_t b);
uint64_t toggleBit(uint64_t b, int n);
uint64_t setBit(uint64_t b, int n);
uint64_t clearBit(uint64_t b, int n);
int getBit(uint64_t b, int n);

/* ---- PRINT FUNCTIONS ---- */
void printBitBoard(const uint64_t& b);

#endif // BITOPS_H