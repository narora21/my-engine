//
//  pawn.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/23/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "pawn.h"
#include "bitops.h"
#include <iostream>


/* ---- PAWN PUSH TARGETS ---- */

// gets target squares of single white pawn pushes
uint64_t whiteSinglePushTargets(const uint64_t& whitePawns, const uint64_t& emptyBoard) {
   return northOne(whitePawns) & emptyBoard;
}
// gets target squares of double white pawn pushes
uint64_t whiteDoublePushTargets(const uint64_t& whitePawns, const uint64_t& emptyBoard) {
   uint64_t singlePushes = whiteSinglePushTargets(whitePawns, emptyBoard);
   return northOne(singlePushes) & emptyBoard & RANK_4;
}
// gets target squares of single black pawn pushes
uint64_t blackSinglePushTargets(const uint64_t& blackPawns, const uint64_t& emptyBoard) {
   return southOne(blackPawns) & emptyBoard;
}
// gets target squares of double black pawn pushes
uint64_t blackDoublePushTargets(const uint64_t& blackPawns, const uint64_t& emptyBoard) {
   uint64_t singlePushes = blackSinglePushTargets(blackPawns, emptyBoard);
   return southOne(singlePushes) & emptyBoard & RANK_5;
}




/* ---- PAWN PUSH SOURCES ---- */

// gets source squares of single white pawn pushes
uint64_t whiteSinglePushSources(const uint64_t& whitePawns, const uint64_t& emptyBoard) {
   return southOne(emptyBoard) & whitePawns;
}
// gets source squares of double white pawn pushes
uint64_t whiteDoublePushSources(const uint64_t& whitePawns, const uint64_t& emptyBoard) {
   uint64_t emptyRank3 = southOne(emptyBoard & RANK_4) & emptyBoard;
   return whiteSinglePushSources(whitePawns, emptyRank3);
}
// gets source squares of single black pawn pushes
uint64_t blackSinglePushSources(const uint64_t& blackPawns, const uint64_t& emptyBoard) {
   return northOne(emptyBoard) & blackPawns;
}
// gets source squares of double black pawn pushes
uint64_t blackDoublePushSources(const uint64_t& blackPawns, const uint64_t& emptyBoard) {
   uint64_t emptyRank6 = northOne(emptyBoard & RANK_5) & emptyBoard;
   return blackSinglePushSources(blackPawns, emptyRank6);
}



/* ---- PAWN ATTACKS ---- */
uint64_t arrPawnAttacks[NUM_COLORS][NUM_SQUARES];
bool arrPawnAttacksInitialized = false;
// pre-compute pawn attacks according to square and color
void computePawnAttacks(){
   if(!arrPawnAttacksInitialized){
      for(int i = 0; i < NUM_SQUARES; i++){
         uint64_t pawn = 1;
         pawn = pawn << i;
         arrPawnAttacks[nWhite][i] = whitePawnAnyAttacks(pawn);
         arrPawnAttacks[nBlack][i] = blackPawnAnyAttacks(pawn);
      }
      arrPawnAttacksInitialized = true;
   }
}
// lookup pawn attacks
uint64_t lookupPawnAttacks(Square pawn, Color color){
   if(arrPawnAttacksInitialized){
      if(pawn == none){
         std::cerr << "None square provided to pawn attacks lookup" << std::endl;
         return 0;
      }
      return arrPawnAttacks[color][pawn];
   }
   else{
      //error
      std::cerr << "Error: attempted to access pawn attacks array before array initialization" << std::endl;
      exit(EXIT_FAILURE);
   }
}
// squares attacked by white pawns
uint64_t whitePawnEastAttacks(const uint64_t& whitePawns) {
   return noEaOne(whitePawns) & NOT_A_FILE;
}
uint64_t whitePawnWestAttacks(const uint64_t& whitePawns) {
   return noWeOne(whitePawns) & NOT_H_FILE;
}
// squares attacked by black pawns
uint64_t blackPawnEastAttacks(const uint64_t& blackPawns) {
   return soEaOne(blackPawns) & NOT_A_FILE;
}
uint64_t blackPawnWestAttacks(const uint64_t& blackPawns) {
   return soWeOne(blackPawns) & NOT_H_FILE;
}
// all squares attacked by white pawns
uint64_t whitePawnAnyAttacks(const uint64_t& whitePawns) {
   return whitePawnEastAttacks(whitePawns) | whitePawnWestAttacks(whitePawns);
}
// squares attacked by 2 white pawns
uint64_t whitePawnDoubleAttacks(const uint64_t& whitePawns) {
   return whitePawnEastAttacks(whitePawns) & whitePawnWestAttacks(whitePawns);
}
// squares attacked by a single white pawn
uint64_t whitePawnSingleAttacks(const uint64_t& whitePawns) {
   return whitePawnEastAttacks(whitePawns) ^ whitePawnWestAttacks(whitePawns);
}
// all squares attacked by black pawns
uint64_t blackPawnAnyAttacks(const uint64_t& blackPawns) {
   return blackPawnEastAttacks(blackPawns) | blackPawnWestAttacks(blackPawns);
}
// squares attacked by 2 black pawns
uint64_t blackPawnDoubleAttacks(const uint64_t& blackPawns) {
   return blackPawnEastAttacks(blackPawns) & blackPawnWestAttacks(blackPawns);
}
// squares attacked by a single black pawn
uint64_t blackPawnSingleAttacks(const uint64_t& blackPawns) {
   return blackPawnEastAttacks(blackPawns) ^ blackPawnWestAttacks(blackPawns);
}



/* ---- PAWN CAPTURES ---- */

// returns the pawns that can execute a capture
uint64_t whitePawnAttackersEast(const uint64_t& whitePawns, const uint64_t& blackPieces){
   return whitePawns & blackPawnWestAttacks(blackPieces);
}
uint64_t whitePawnAttackersWest(const uint64_t& whitePawns, const uint64_t& blackPieces){
   return whitePawns & blackPawnEastAttacks(blackPieces);
}
uint64_t whitePawnAttackersAny(const uint64_t& whitePawns, const uint64_t& blackPieces){
   return whitePawns & blackPawnAnyAttacks(blackPieces);
}
uint64_t blackPawnAttackersEast(const uint64_t& blackPawns, const uint64_t& whitePieces){
   return blackPawns & whitePawnWestAttacks(whitePieces);
}
uint64_t blackPawnAttackersWest(const uint64_t& blackPawns, const uint64_t& whitePieces){
   return blackPawns & whitePawnEastAttacks(whitePieces);
}
uint64_t blackPawnAttackersAny(const uint64_t& blackPawns, const uint64_t& whitePieces){
   return blackPawns & whitePawnAnyAttacks(whitePieces);
}



/* ---- PAWN RAMS ---- */

uint64_t whitePawnRams(const uint64_t& whitePawns, const uint64_t& blackPawns){
   return southOne(blackPawns) & whitePawns;
}
uint64_t blackPawnRams(const uint64_t& whitePawns, const uint64_t& blackPawns){
   return northOne(whitePawns) & blackPawns;
}



/* ---- PAWN LEVERS ---- */

// white levers
uint64_t whiteEastLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return whitePawns & blackPawnWestAttacks(blackPawns);
}

uint64_t whiteWestLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return whitePawns & blackPawnEastAttacks(blackPawns);
}

uint64_t whiteAnyLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return whiteEastLever(whitePawns, blackPawns) | whiteWestLever(whitePawns, blackPawns);
}
// black levers
uint64_t blackEastLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return blackPawns & whitePawnWestAttacks(whitePawns);
}

uint64_t blackWestLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return blackPawns & whitePawnEastAttacks(whitePawns);
}

uint64_t blackAnyLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return blackEastLever(blackPawns, whitePawns) | blackWestLever(blackPawns, whitePawns);
}
// inner, outer, and center levers
uint64_t whiteInnerLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return ( whiteEastLever(whitePawns, blackPawns) & ABC_FILES)
        | ( whiteWestLever(whitePawns, blackPawns) & FGH_FILES);
}

uint64_t whiteOuterLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return ( whiteEastLever(whitePawns, blackPawns) & EFG_FILES)
        | ( whiteWestLever(whitePawns, blackPawns) & BCD_FILES);
}

uint64_t whiteCenterLever(const uint64_t& whitePawns, const uint64_t& blackPawns) {
   return ( whiteEastLever(whitePawns, blackPawns) & D_FILE)
        | ( whiteWestLever(whitePawns, blackPawns) & E_FILE);
}
uint64_t blackInnerLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return ( blackEastLever(blackPawns, whitePawns) & ABC_FILES)
        | ( blackWestLever(blackPawns, whitePawns) & FGH_FILES);
}

uint64_t blackOuterLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return ( blackEastLever(blackPawns, whitePawns) & EFG_FILES)
        | ( blackWestLever(blackPawns, whitePawns) & BCD_FILES);
}

uint64_t blackCenterLever(const uint64_t& blackPawns, const uint64_t& whitePawns) {
   return ( blackEastLever(blackPawns, whitePawns) & D_FILE)
        | ( blackWestLever(blackPawns, whitePawns) & E_FILE);
}