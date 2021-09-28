//
//  main.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include <iostream>
#include "constants.h"
#include "board.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "bitops.h"
#include "unittests.h"
#include "fen.h"

using namespace std;

int main(int argc, char* argv[]){
	#ifdef DEBUG
		cerr << "Running unit tests..." << endl;
		//testFen();
		//std::string s1 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1 ";
		//Board b(s1);
		//b.printAllBitBoards();
		//std::string s2 = "rnb1k1nr/pppppppp/8/4N3/2q3b1/8/PPPPPPPP/R1BQKB1R w KQkq - 0 1";
		//Board b(s2);
		//b.printBoard();
		//b.printBoard(knightAttacks(b.getKnights(nWhite)));
		std::string s3 = "1n2k2r/ppp2ppp/3p4/2bKp3/2n1r3/8/PPPPPPPP/R1BQ1B2 w k - 0 1";
		Board b(s3);
		b.printBoard();
		b.printBoard(kingAttacks(b.getKing(nWhite)));
		return 0;
	#endif // DEBUG

	cout << "Running the engine..." << endl;

	return 0;
}