//
//  main.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include <iostream>
#include <string>
#include <chrono>
#include "constants.h"
#include "perft.h"
#include "engine.h"

using namespace std::chrono;

int main(int argc, char* argv[]){
	init();
	#ifdef DEBUG
		std::cout << "Running unit tests..." << std::endl;
		for(int i = 0; i < 8; i++){
			auto start = high_resolution_clock::now();
			uint64_t results = perft(i);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			std::cout << "Perft (depth=" << i << "): " << results;
			std::cout << " (" << duration.count() << " s)" << std::endl;
		}
		return 0;
	#endif // DEBUG

	std::cout << "Running the engine..." << std::endl;

	return 0;
}