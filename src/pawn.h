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
uint64_t whiteSinglePushTargets(const uint64_t& whitePawns, const uint64_t& emptyBoard);
// gets target squares of double white pawn pushes
uint64_t whiteDoublePushTargets(const uint64_t& whitePawns, const uint64_t& emptyBoard);
// gets target squares of single black pawn pushes
uint64_t blackSinglePushTargets(const uint64_t& blackPawns, const uint64_t& emptyBoard);
// gets target squares of double black pawn pushes
uint64_t blackDoublePushTargets(const uint64_t& blackPawns, const uint64_t& emptyBoard);



/* ---- PAWN PUSH SOURCES ---- */
// gets source squares of single white pawn pushes
uint64_t whiteSinglePushSources(const uint64_t& whitePawns, const uint64_t& emptyBoard);
// gets source squares of double white pawn pushes
uint64_t whiteDoublePushSources(const uint64_t& whitePawns, const uint64_t& emptyBoard);
// gets source squares of single black pawn pushes
uint64_t blackSinglePushSources(const uint64_t& blackPawns, const uint64_t& emptyBoard);
// gets source squares of double black pawn pushes
uint64_t blackDoublePushSources(const uint64_t& blackPawns, const uint64_t& emptyBoard);



/* ---- PAWN ATTACKS ---- */
// initializes pre-computed pawn attacks
void computePawnAttacks();
// lookup pawn attacks
uint64_t lookupPawnAttacks(const Square& pawn, const Color& color);
// attacked squares of pawns
uint64_t whitePawnEastAttacks(const uint64_t& whitePawns);
uint64_t whitePawnWestAttacks(const uint64_t& whitePawns);
uint64_t blackPawnEastAttacks(const uint64_t& blackPawns);
uint64_t blackPawnWestAttacks(const uint64_t& blackPawns);

// pawn attacks, double attacks, and single attacks 
uint64_t whitePawnAnyAttacks(const uint64_t& whitePawns);
uint64_t whitePawnDoubleAttacks(const uint64_t& whitePawns);
uint64_t whitePawnSingleAttacks(const uint64_t& whitePawns);

uint64_t blackPawnAnyAttacks(const uint64_t& blackPawns);
uint64_t blackPawnDoubleAttacks(const uint64_t& blackPawns);
uint64_t blackPawnSingleAttacks(const uint64_t& blackPawns);



/* ---- PAWN CAPTURES ---- */
// returns the pawns that can execute a capture
uint64_t whitePawnAttackersEast(const uint64_t& whitePawns, const uint64_t& blackPieces);
uint64_t whitePawnAttackersWest(const uint64_t& whitePawns, const uint64_t& blackPieces);
uint64_t whitePawnAttackersAny(const uint64_t& whitePawns, const uint64_t& blackPieces);
uint64_t blackPawnAttackersEast(const uint64_t& blackPawns, const uint64_t& whitePieces);
uint64_t blackPawnAttackersWest(const uint64_t& blackPawns, const uint64_t& whitePieces);
uint64_t blackPawnAttackersAny(const uint64_t& blackPawns, const uint64_t& whitePieces);



/* ---- PAWN RAMS ---- */
// rams: black and white pawns that block each other from advancing
// # white pawn rams == # black pawn rams
uint64_t whitePawnRams(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t blackPawnRams(const uint64_t& whitePawns, const uint64_t& blackPawns);


/* ---- PAWN LEVERS ---- */
// levers: pawns that can capture each other
// inner lever: lever that can capture towards the center
// outer lever: lever that can capture away from the center
// center lever: levers in the center 2 files (e and d)
uint64_t whiteEastLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t whiteWestLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t whiteAnyLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
// Note: the black levers can be computed from white levers:
// blackEastLever = whiteWestLever << 7;
// blackWestLever = whiteEastLever << 9
uint64_t blackEastLever(const uint64_t& blackPawns, const uint64_t& whitePawns);
uint64_t blackWestLever(const uint64_t& blackPawns, const uint64_t& whitePawns);
uint64_t blackAnyLever(const uint64_t& blackPawns, const uint64_t& whitePawns);
// inner, outer, and center levers:
uint64_t whiteInnerLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t whiteOuterLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t whiteCenterLever(const uint64_t& whitePawns, const uint64_t& blackPawns);
uint64_t blackInnerLever(const uint64_t& blackPawns, const uint64_t& whitePawns);
uint64_t blackOuterLever(const uint64_t& blackPawns, const uint64_t& whitePawns);
uint64_t blackCenterLever(const uint64_t& blackPawns, const uint64_t& whitePawns);

#endif //PAWN_H