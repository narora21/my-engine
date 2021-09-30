//
//  movegen.h
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "move.h"

int generateMoves(const Board& position, Move legal_moves[NUM_MOVES]);

#endif //MOVEGEN_H