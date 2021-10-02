//
//  pawn.h
//  My Engine
//
//  Created by Nikhil Arora on 9/23/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//
#ifndef PAWN_H
#define PAWN_H

#include <cstdint>
#include "constants.h"


/* ---- PAWN PUSH TARGETS ---- */
// gets target squares of single white pawn pushes
uint64_t whiteSinglePushTargets(uint64_t whitePawns, uint64_t emptyBoard);
// gets target squares of double white pawn pushes
uint64_t whiteDoublePushTargets(uint64_t whitePawns, uint64_t emptyBoard);
// gets target squares of single black pawn pushes
uint64_t blackSinglePushTargets(uint64_t blackPawns, uint64_t emptyBoard);
// gets target squares of double black pawn pushes
uint64_t blackDoublePushTargets(uint64_t blackPawns, uint64_t emptyBoard);



/* ---- PAWN PUSH SOURCES ---- */
// gets source squares of single white pawn pushes
uint64_t whiteSinglePushSources(uint64_t whitePawns, uint64_t emptyBoard);
// gets source squares of double white pawn pushes
uint64_t whiteDoublePushSources(uint64_t whitePawns, uint64_t emptyBoard);
// gets source squares of single black pawn pushes
uint64_t blackSinglePushSources(uint64_t blackPawns, uint64_t emptyBoard);
// gets source squares of double black pawn pushes
uint64_t blackDoublePushSources(uint64_t blackPawns, uint64_t emptyBoard);



/* ---- PAWN ATTACKS ---- */
// initializes pre-computed pawn attacks
void initPawnAttacks();
// lookup pawn attacks
uint64_t lookupPawnAttacks(Square pawn, Color color);
// attacked squares of pawns
uint64_t whitePawnEastAttacks(uint64_t whitePawns);
uint64_t whitePawnWestAttacks(uint64_t whitePawns);
uint64_t blackPawnEastAttacks(uint64_t blackPawns);
uint64_t blackPawnWestAttacks(uint64_t blackPawns);

// pawn attacks, double attacks, and single attacks 
uint64_t whitePawnAnyAttacks(uint64_t whitePawns);
uint64_t whitePawnDoubleAttacks(uint64_t whitePawns);
uint64_t whitePawnSingleAttacks(uint64_t whitePawns);

uint64_t blackPawnAnyAttacks(uint64_t blackPawns);
uint64_t blackPawnDoubleAttacks(uint64_t blackPawns);
uint64_t blackPawnSingleAttacks(uint64_t blackPawns);



/* ---- PAWN CAPTURES ---- */
// returns the pawns that can execute a capture
uint64_t whitePawnAttackersEast(uint64_t whitePawns, uint64_t blackPieces);
uint64_t whitePawnAttackersWest(uint64_t whitePawns, uint64_t blackPieces);
uint64_t whitePawnAttackersAny(uint64_t whitePawns, uint64_t blackPieces);
uint64_t blackPawnAttackersEast(uint64_t blackPawns, uint64_t whitePieces);
uint64_t blackPawnAttackersWest(uint64_t blackPawns, uint64_t whitePieces);
uint64_t blackPawnAttackersAny(uint64_t blackPawns, uint64_t whitePieces);



/* ---- PAWN RAMS ---- */
// rams: black and white pawns that block each other from advancing
// # white pawn rams == # black pawn rams
uint64_t whitePawnRams(uint64_t whitePawns, uint64_t blackPawns);
uint64_t blackPawnRams(uint64_t whitePawns, uint64_t blackPawns);


/* ---- PAWN LEVERS ---- */
// levers: pawns that can capture each other
// inner lever: lever that can capture towards the center
// outer lever: lever that can capture away from the center
// center lever: levers in the center 2 files (e and d)
uint64_t whiteEastLever(uint64_t whitePawns, uint64_t blackPawns);
uint64_t whiteWestLever(uint64_t whitePawns, uint64_t blackPawns);
uint64_t whiteAnyLever(uint64_t whitePawns, uint64_t blackPawns);
// Note: the black levers can be computed from white levers:
// blackEastLever = whiteWestLever << 7;
// blackWestLever = whiteEastLever << 9
uint64_t blackEastLever(uint64_t blackPawns, uint64_t whitePawns);
uint64_t blackWestLever(uint64_t blackPawns, uint64_t whitePawns);
uint64_t blackAnyLever(uint64_t blackPawns, uint64_t whitePawns);
// inner, outer, and center levers:
uint64_t whiteInnerLever(uint64_t whitePawns, uint64_t blackPawns);
uint64_t whiteOuterLever(uint64_t whitePawns, uint64_t blackPawns);
uint64_t whiteCenterLever(uint64_t whitePawns, uint64_t blackPawns);
uint64_t blackInnerLever(uint64_t blackPawns, uint64_t whitePawns);
uint64_t blackOuterLever(uint64_t blackPawns, uint64_t whitePawns);
uint64_t blackCenterLever(uint64_t blackPawns, uint64_t whitePawns);

#endif //PAWN_H