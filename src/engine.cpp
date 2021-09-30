//
//  engine.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "engine.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include <iostream>

// initialize engine pre-requisites
bool engineInitialized = false;
bool engineIsInitialized(){
	return engineInitialized;
}
void init(){
	std::cout << "Initializing engine..." << std::endl;
	// compute piece attack tables
	computePawnAttacks();
	computeKnightAttacks();
	initMagicBishopTable();
	initMagicRookTable();
	computeKingAttacks();
	engineInitialized = true;
}