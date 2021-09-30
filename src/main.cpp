//
//  main.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include <iostream>
#include <string>
#include "constants.h"
#include "board.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "bitops.h"
#include "unittests.h"
#include "fen.h"
#include "engine.h"

int main(int argc, char* argv[]){
	init();
	#ifdef DEBUG
		std::cout << "Running unit tests..." << std::endl;
		//testFen();
		std::string s1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";
		std::string castle = "r3kbnr/pppqpppp/2npb3/8/4P3/3P1N2/PPP1BPPP/RNBQK2R w KQkq - 0 1";
		Board b1(castle);
		b1.testMakeMove();
		//Move m((unsigned int)e4, (unsigned int)e2, (unsigned int) 1);
		//b1.makeMove(m);
		//b1.printBoard();
		//b1.printAllBitBoards();
		//std::string s2 = "rnb1k1nr/pppppppp/8/4N3/2q3b1/8/PPPPPPPP/R1BQKB1R w KQkq - 0 1";
		//Board b2(s2);
		//b2.printBoard();
		//b2.printBoard(knightAttacks(b2.getKnights(nWhite)));
		//std::string s3 = "1n2k2r/ppp2ppp/3p4/2bKp3/2n1r3/8/PPPP1PPP/R1BQ1B2 w k - 0 1";
		//Board b3(s3);
		//b3.printBoard();
		//computeKnightAttacks();
		//b3.printBoard(lookupKnightAttacks(a1));
		//std::string s4 = "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp w k - 0 1";
		//Board b4(s4);
		//uint64_t attacks = lookupRookAttacks(e4, b1.getAllPieces());
		//b4.printBoard(attacks);
		//std::string s5 = "rnbqk1nr/ppppppbp/6p1/4K3/8/8/PPPPPPPP/RNBQ1BNR w kq - 0 1";
		//Board b5(s5);
		//uint64_t attacks5 = b5.attacksTo(e5);
		//b5.printBoard(attacks5);
		return 0;
	#endif // DEBUG

	std::cout << "Running the engine..." << std::endl;

	return 0;
}