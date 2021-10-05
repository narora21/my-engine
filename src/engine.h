//
//  engine.h
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"
#include "constants.h"

/* ---- EVALUATION STRUCT ---- */
typedef struct{
	float score;
	Move best_move;
	uint64_t nodes_searched;
} Eval;

/* ---- CORE ENGINE ---- */
// initialize engine pre-requisites
void init();
void runEngine();

/* ---- EVALUATION METHODS ---- */
float materialCount(const Board& b, Color side);

/* ---- SEARCH ALGORITHMS ---- */
Eval minimax(Board& board, int depth, float (*evaluate)(const Board&));
Eval alphabeta(Board& board, int depth, float (*evaluate)(const Board&));

#endif //ENGINE_H