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
#include "bitops.h"
#include "unittests.h"
#include "fen.h"

using namespace std;

int main(int argc, char* argv[]){
	#ifdef DEBUG
		cerr << "Running unit tests..." << endl;
		//testFen();
		std::string s = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1 ";
		Board b(s);
		b.printAllBitBoards();
		return 0;
	#endif // DEBUG

	cout << "Running the engine..." << endl;

	return 0;
}