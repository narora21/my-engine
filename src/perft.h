//
//  perft.h
//  My Engine
//
//  Created by Nikhil Arora on 10/2/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef PERFT_H
#define PERFT_H

#include "constants.h"
#include "board.h"

typedef struct{
	uint64_t nodes;
	uint64_t captures;
	uint64_t en_passants;
	uint64_t castles;
	uint64_t promos;
} PerftCounts;

/* ---- PERFT TEST ---- */
// perft to test pseduolegal move generation
uint64_t perft(Board& board, int depth);
uint64_t perft(int depth);
PerftCounts detailedPerft(Board& board, int depth);
void perftCount(Board& board, int depth);


#endif //PERFT_H