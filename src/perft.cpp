//
//  perft.cpp
//  My Engine
//
//  Created by Nikhil Arora on 10/2/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "perft.h"
#include "move.h"
#include "movegen.h"

// perft to test pseduolegal move generation
uint64_t _perft(Board& b, int depth){
	if(depth == 0)
		return 1ULL;
	std::vector<Move> move_list;
	uint64_t nodes = 0;
	generateMoves(b, move_list);
	Color side = b.getSideToMove();
	for(size_t i = 0; i < move_list.size(); i++){
		b.makeMove(move_list[i]);
		if(!b.inCheck(side))
			nodes += _perft(b, depth - 1);
		b.unmakeMove();
	}
	return nodes;
}

// perft driver code
uint64_t perft(int depth){
	Board b;
	return _perft(b, depth);	
}