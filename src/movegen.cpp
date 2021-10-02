//
//  movegen.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/29/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "movegen.h"
#include "constants.h"
#include "bitops.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include <iostream>

// generates all pseudo-legal moves in a given position
// input: Board: the current position
// 		  pseudo_legal_moves: array to be filled of legal moves in the position
void generateMoves(const Board& position, std::vector<Move>& pseudo_legals){
	Color side_to_move = position.getSideToMove();
	Color opponent_color = (Color)(side_to_move ^ 1);
	Square ep_square = position.getEnPassantTarget();
	uint64_t all_pieces = position.getAllPieces(); 
	uint64_t empty_board = ~all_pieces;
	uint64_t opponent_pieces = position.getAllColorPieces(opponent_color);
	unsigned int to, from;


	/* ---- COLOR DEPENDANT ASSIGNMENTS ---- */
	uint64_t kingside_castle_mask, queenside_castle_mask;
	Square kingside_castle_to, queenside_castle_to;
	bool kingside_thru_check, queenside_thru_check;
	uint64_t pawns = position.getPawns(side_to_move);
	uint64_t single_sources, single_targets, double_sources, double_targets,
			 pawn_attackers, ep_attacker, promo_sources, promo_pushes, promo_attackers;
	if(side_to_move == nWhite){
		// pawn bit boards
		uint64_t s_s = whiteSinglePushSources(pawns, empty_board);
		uint64_t s_t = whiteSinglePushTargets(pawns, empty_board);
		single_sources = s_s & NOT_RANK_7;
		single_targets = s_t & NOT_RANK_8;
		promo_sources = s_s & RANK_7;
		promo_pushes = s_t & RANK_8;
		double_sources = whiteDoublePushSources(pawns, empty_board);
		double_targets = whiteDoublePushTargets(pawns, empty_board);
		uint64_t att = whitePawnAttackersAny(pawns, opponent_pieces);
		pawn_attackers = att & NOT_RANK_7;
		promo_attackers = att & RANK_7;
		// castling conditions
		kingside_castle_to = g1;
		queenside_castle_to = c1;
		kingside_castle_mask = inBetween(e1, h1);
		queenside_castle_mask = inBetween(e1, a1);
		kingside_thru_check = position.attacked(f1, opponent_color) ||
							  position.attacked(g1, opponent_color);
		queenside_thru_check = position.attacked(b1, opponent_color) ||
							   position.attacked(c1, opponent_color) ||
							   position.attacked(d1, opponent_color);
	}
	else{
		// pawn bitboards
		uint64_t s_s = blackSinglePushSources(pawns, empty_board);
		uint64_t s_t = blackSinglePushTargets(pawns, empty_board);
		single_sources = s_s & NOT_RANK_2;
		single_targets = s_t & NOT_RANK_1;
		promo_sources = s_s & RANK_2;
		promo_pushes = s_t & RANK_1;
		double_sources = blackDoublePushSources(pawns, empty_board);
		double_targets = blackDoublePushTargets(pawns, empty_board);
		uint64_t att = blackPawnAttackersAny(pawns, opponent_pieces);
		pawn_attackers = att & NOT_RANK_2;
		promo_attackers = att & RANK_2;
		// castling conditions
		kingside_castle_to = g8;
		queenside_castle_to = c8;
		kingside_castle_mask = inBetween(e8, h8);
		queenside_castle_mask = inBetween(e8, a8);
		kingside_thru_check = position.attacked(f8, opponent_color) ||
							  position.attacked(g8, opponent_color);
		queenside_thru_check = position.attacked(b8, opponent_color) ||
							   position.attacked(c8, opponent_color) ||
							   position.attacked(d8, opponent_color);
	}


	/* ---- PAWN MOVES ---- */
	// single push
	while(single_sources){
		from = getLS1bIndex(single_sources);
		to = getLS1bIndex(single_targets);
		pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
		single_sources = clearLS1b(single_sources);
		single_targets = clearLS1b(single_targets);
	}
	// double push
	while(double_sources){
		from = getLS1bIndex(double_sources);
		to = getLS1bIndex(double_targets);
		pseudo_legals.push_back(Move(to, from, DOUBLE_PAWN_MOVE_CODE));
		double_sources = clearLS1b(double_sources);
		double_targets = clearLS1b(double_targets);
	}
	// pawn capture
	while(pawn_attackers){
		from = getLS1bIndex(pawn_attackers);
		uint64_t attacks = lookupPawnAttacks((Square)from, side_to_move) & opponent_pieces;
		to = getLS1bIndex(attacks);
		pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
		attacks = clearLS1b(attacks);
		if(attacks){
			to = getLS1bIndex(attacks);
			pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
		}
		pawn_attackers = clearLS1b(pawn_attackers);
	}
	// en passant
	if(ep_square != noneSquare){
		ep_attacker = lookupPawnAttacks(ep_square, opponent_color) & pawns;
		while(ep_attacker){
			from = getLS1bIndex(ep_attacker);
			to = (unsigned int) ep_square;
			pseudo_legals.push_back(Move(to, from, EN_PASSANT_CODE));
			ep_attacker = clearLS1b(ep_attacker);
		}
	}
	// promo
	while(promo_sources){
		from = getLS1bIndex(promo_sources);
		to = getLS1bIndex(promo_pushes);
		pseudo_legals.push_back(Move(to, from, KNIGHT_PROMO_CODE));
		pseudo_legals.push_back(Move(to, from, BISHOP_PROMO_CODE));
		pseudo_legals.push_back(Move(to, from, ROOK_PROMO_CODE));
		pseudo_legals.push_back(Move(to, from, QUEEN_PROMO_CODE));
		promo_sources = clearLS1b(promo_sources);
		promo_pushes = clearLS1b(promo_pushes);
	}
	// capture promo
	while(promo_attackers){
		from = getLS1bIndex(promo_attackers);
		uint64_t attacks = lookupPawnAttacks((Square)from, side_to_move) & opponent_pieces;
		while(attacks){
			to = getLS1bIndex(attacks);
			pseudo_legals.push_back(Move(to, from, KNIGHT_PROMO_CAPTURE_CODE));
			pseudo_legals.push_back(Move(to, from, BISHOP_PROMO_CAPTURE_CODE));
			pseudo_legals.push_back(Move(to, from, ROOK_PROMO_CAPTURE_CODE));
			pseudo_legals.push_back(Move(to, from, QUEEN_PROMO_CAPTURE_CODE));
			attacks = clearLS1b(attacks);
		}
		promo_attackers = clearLS1b(promo_attackers);
	}


	/* ---- KNIGHT MOVES ---- */
	uint64_t knights = position.getKnights(side_to_move);
	while(knights){
		from = getLS1bIndex(knights);
		uint64_t knight_moves = lookupKnightAttacks((Square) from);
		uint64_t quiet_knight_moves = knight_moves & empty_board;
		uint64_t attack_knight_moves = knight_moves & opponent_pieces;
		// moves
		while(quiet_knight_moves){
			to = getLS1bIndex(quiet_knight_moves);
			pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
			quiet_knight_moves = clearLS1b(quiet_knight_moves);
		}
		// captures
		while(attack_knight_moves){
			to = getLS1bIndex(attack_knight_moves);
			pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
			attack_knight_moves = clearLS1b(attack_knight_moves);
		}
		knights = clearLS1b(knights);
	}


	/* ---- KING MOVES ---- */
	uint64_t king = position.getKing(side_to_move);
	from = getLS1bIndex(king);
	uint64_t king_moves = lookupKingAttacks((Square) from);
	// moves
	uint64_t quiet_king_moves = king_moves & empty_board;
	while(quiet_king_moves){
		to = getLS1bIndex(quiet_king_moves);
		pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
		quiet_king_moves = clearLS1b(quiet_king_moves);
	}
	// captures
	uint64_t king_attacks = king_moves & opponent_pieces;
	while(king_attacks){
		to = getLS1bIndex(king_attacks);
		pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
		king_attacks = clearLS1b(king_attacks);
	}
	// king side castle
	bool can_castle_kingside = position.getCastleAbility((side_to_move << 1));
	can_castle_kingside = can_castle_kingside && ((kingside_castle_mask & all_pieces) == 0);
	if(can_castle_kingside && !kingside_thru_check){
		to = kingside_castle_to;
		pseudo_legals.push_back(Move(to, from, KINGISDE_CASTLE_CODE));
	}
	// queen side castle
	bool can_castle_queenside = position.getCastleAbility(1 + (side_to_move << 1));
	can_castle_queenside = can_castle_queenside && ((queenside_castle_mask & all_pieces) == 0);
	if(can_castle_queenside && !queenside_thru_check){
		to = queenside_castle_to;
		pseudo_legals.push_back(Move(to, from, QUEENSIDE_CASTLE_CODE));
	}


	/* ---- BISHOP MOVES ---- */
	uint64_t bishops = position.getBishops(side_to_move);
	while(bishops){
		from = getLS1bIndex(bishops);
		uint64_t bishop_moves = lookupBishopAttacks((Square) from, all_pieces);
		uint64_t quiet_bishop_moves = bishop_moves & empty_board;
		uint64_t bishop_captures = bishop_moves & opponent_pieces;
		// quiet moves
		while(quiet_bishop_moves){
			to = getLS1bIndex(quiet_bishop_moves);
			pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
			quiet_bishop_moves = clearLS1b(quiet_bishop_moves);
		}
		// captures
		while(bishop_captures){
			to = getLS1bIndex(bishop_captures);
			pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
			bishop_captures = clearLS1b(bishop_captures);
		}
		bishops = clearLS1b(bishops);
	}


	/* ---- ROOK MOVES ---- */
	uint64_t rooks = position.getRooks(side_to_move);
	while(rooks){
		from = getLS1bIndex(rooks);
		uint64_t rook_moves = lookupRookAttacks((Square) from, all_pieces);
		uint64_t quiet_rook_moves = rook_moves & empty_board;
		uint64_t rook_captures = rook_moves & opponent_pieces;
		// quiet moves
		while(quiet_rook_moves){
			to = getLS1bIndex(quiet_rook_moves);
			pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
			quiet_rook_moves = clearLS1b(quiet_rook_moves);
		}
		// captures
		while(rook_captures){
			to = getLS1bIndex(rook_captures);
			pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
			rook_captures = clearLS1b(rook_captures);
		}
		rooks = clearLS1b(rooks);
	}
	

	/* ---- QUEEN MOVES ---- */
	uint64_t queens = position.getQueens(side_to_move);
	while(queens){
		from = getLS1bIndex(queens);
		uint64_t queen_moves = lookupRookAttacks((Square) from, all_pieces) |
							   lookupBishopAttacks((Square) from, all_pieces);
		uint64_t quiet_queen_moves = queen_moves & empty_board;
		uint64_t queen_captures = queen_moves & opponent_pieces;
		// moves
		while(quiet_queen_moves){
			to = getLS1bIndex(quiet_queen_moves);
			pseudo_legals.push_back(Move(to, from, QUIET_MOVE_CODE));
			quiet_queen_moves = clearLS1b(quiet_queen_moves);
		}
		// captures
		while(queen_captures){
			to = getLS1bIndex(queen_captures);
			pseudo_legals.push_back(Move(to, from, CAPTURE_CODE));
			queen_captures = clearLS1b(queen_captures);
		}
		queens = clearLS1b(queens);
	}
}