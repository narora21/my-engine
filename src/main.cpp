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
#include "unittests.h"
#include "engine.h"

int main(int argc, char* argv[]){
	init();
	#ifdef DEBUG
		std::cout << "Running unit tests..." << std::endl;
		testPerftAll();
		return 0;
	#endif // DEBUG END

	std::cout << "Running the engine..." << std::endl;
	runEngine();
	return 0;
}