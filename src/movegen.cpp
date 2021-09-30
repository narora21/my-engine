//
//  movegen.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "movegen.h"
#include "constants.h"

// generates all legal moves in a given position
// input: Board: the current position
// 		  legal_moves: array to be filled of legal moves in the position
// output: number of legal moves found
int generateMoves(const Board& position, Move legal_moves[NUM_MOVES]){
	Color side_to_move = position.getSideToMove();
	Square ep_square = position.getEnPassantTarget(); 
	// pawn moves
	// knight moves
	// king moves
	// bishop and queen moves
	// rook and queen moves
	return 0;
}