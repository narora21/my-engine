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

int main(int argc, char* argv[]){
	#ifdef DEBUG
		std::cout << "Running unit tests..." << std::endl;
		//testFen();
		std::string s1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq e3 0 1 ";
		Board b1(s1);
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
		std::string s4 = "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp w k - 0 1";
		Board b4(s4);
		initMagicBishopTable();
		for(int i = 0; i < 64; i++){
			uint64_t attacks = lookupBishopAttacks((Square)i, b1.getAllPieces());
			b4.printBoard(attacks);
		}
		return 0;
	#endif // DEBUG

	std::cout << "Running the engine..." << std::endl;

	return 0;
}