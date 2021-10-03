//
//  unittests.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/24/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "unittests.h"
#include <string>
#include <chrono>
#include <iostream>
#include "board.h"
#include "perft.h"
using namespace std::chrono;

/* ---- BITBOARD TESTS ---- */

/* ---- PAWN TESTS ---- */

/* ---- PERFT TESTS ---- */
void testPerft(Board& board, int depth, uint64_t* expected){
	auto perft_start = high_resolution_clock::now();
	uint64_t total_nodes = 0;
	for(int i = 1; i <= depth; i++){
		std::cout << "Perft (depth=" << i << "): " << std::flush;
		auto start = high_resolution_clock::now();
		uint64_t results = perft(board, i);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		std::cout << results << " (" << ((double)duration.count())/1000 << " s)" << std::flush;
		if(expected[i-1] != results)
			std::cout << " error: expected: " << expected[i-1];
		std::cout << std::endl;
		total_nodes += results;
	}
	auto perft_stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(perft_stop - perft_start);
	double nodes_per_second = total_nodes/((double)duration.count());
	double Mnps = nodes_per_second / 1000000.0;
	std::cout << "Average number of nodes processed per second: ~" << Mnps << " Mnps" << std::endl;
	std::cout << std::endl;
}
void testDetailedPerft(Board& board, int depth, uint64_t* expected){
	for(int i = 1; i <= depth; i++){
		std::cout << "Perft (depth=" << i << "): " << std::flush;
		auto start = high_resolution_clock::now();
		PerftCounts pc = detailedPerft(board, i);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		std::cout << pc.nodes << " (" << ((float)duration.count())/1000 << " s)" << std::flush;
		if(expected[i-1] != pc.nodes)
			std::cout << " error: expected: " << expected[i-1];
		std::cout << std::endl;
		std::cout << "\tCaptures: " << pc.captures << std::endl;
		std::cout << "\tEn Passants: " << pc.en_passants << std::endl;
		std::cout << "\tCastles: " << pc.castles << std::endl;
		std::cout << "\tPromotions: " << pc.promos << std::endl;
	}
	std::cout << std::endl;
}
// PERFT ON INITIAL POSITION
void testPerft1(){
	int depth = 7;
	uint64_t expected[depth] = {20ULL, 400ULL, 8902ULL, 
		197281ULL, 4865609ULL, 119060324ULL, 3195901860ULL};
	Board board;
	std::cout << "Running Perft with initial position: " << std::endl;
	testPerft(board, depth, expected);
}
void testDetailedPerft1(){
	int depth = 7;
	uint64_t expected[depth] = {20ULL, 400ULL, 8902ULL, 
		197281ULL, 4865609ULL, 119060324ULL, 3195901860ULL};
	Board board;
	std::cout << "Running Detailed Perft with initial position: " << std::endl;
	testDetailedPerft(board, depth, expected);
}
// PERFT ON TEST POSITION 2 (MIDDLE GAME)
void testPerft2(){
	int depth = 6;
	uint64_t expected[depth] = {48ULL, 2039ULL, 97862ULL, 4085603ULL,
		193690690ULL, 8031647685};
	Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	std::cout << "Running Perft with test position 2:" << std::endl;
	testPerft(board, depth, expected);
}
void testDetailedPerft2(){
	int depth = 6;
	uint64_t expected[depth] = {48ULL, 2039ULL, 97862ULL, 4085603ULL,
		193690690ULL, 8031647685};
	Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	std::cout << "Running Perft with test position 2:" << std::endl;
	testDetailedPerft(board, depth, expected);
}
void testCountPerft2(){
	int depth = 2;
	Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	std::cout << "Running Count Perft with test position 2:" << std::endl;
	perftCount(board, depth);
}
// PERFT ON TEST POSITION 3 (ENDGAME + EP)
void testPerft3(){
	int depth = 8;
	uint64_t expected[depth] = {14ULL, 191ULL, 2812ULL, 
		43238ULL, 674624ULL, 11030083ULL, 178633661ULL, 3009794393ULL};
	Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	std::cout << "Running Perft with test position 3: " << std::endl;
	testPerft(board, depth, expected);
}
// PERFT ON TEST POSITION 4
void testPerft4(){
	int depth = 6;
	uint64_t expected[depth] = {6ULL, 264ULL, 9467ULL, 
		422333ULL, 15833292ULL, 706045033ULL};
	Board board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	std::cout << "Running Perft with test position 4: " << std::endl;
	testPerft(board, depth, expected);
}
// PERFT ON TEST POSITION 5
void testPerft5(){
	int depth = 5;
	uint64_t expected[depth] = {44ULL, 1486ULL, 62379ULL, 
		2103487ULL, 89941194ULL};
	Board board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 0 1");
	std::cout << "Running Perft with test position 5: " << std::endl;
	testPerft(board, depth, expected);
}
// PERFT ON TEST POSITION 6
void testPerft6(){
	int depth = 6;
	uint64_t expected[depth] = {46ULL, 2079ULL, 89890ULL, 
		3894594ULL, 164075551ULL, 6923051137ULL};
	Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
	std::cout << "Running Perft with test position 6: " << std::endl;
	testPerft(board, depth, expected);
}
// RUN ALL PERFT TESTS
void testPerftAll(){
	auto start = high_resolution_clock::now();
	testPerft1();
	testPerft2();
	testPerft3();
	testPerft4();
	testPerft5();
	testPerft6();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	std::cout << "Tests executed in " << ((double)duration.count()) << " s" << std::endl;
}