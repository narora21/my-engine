//
//  fen.h
//  My Engine
//
//  Created by Nikhil Arora on 9/25/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#ifndef FEN_H
#define FEN_H

/*

FEN STRING GRAMMAR:

<FEN> ::=  <Piece Placement>
       ' ' <Side to move>
       ' ' <Castling ability>
       ' ' <En passant target square>
       ' ' <Halfmove clock>
       ' ' <Fullmove counter>

<Piece Placement> ::= <rank8>'/'<rank7>'/'<rank6>'/'<rank5>'/'<rank4>'/'<rank3>'/'<rank2>'/'<rank1>
<ranki>       ::= [<digit17>]<piece> {[<digit17>]<piece>} [<digit17>] | '8'
<piece>       ::= <white Piece> | <black Piece>
<digit17>     ::= '1' | '2' | '3' | '4' | '5' | '6' | '7'
<white Piece> ::= 'P' | 'N' | 'B' | 'R' | 'Q' | 'K'
<black Piece> ::= 'p' | 'n' | 'b' | 'r' | 'q' | 'k'

<Side to move> ::= {'w' | 'b'}

<Castling ability> ::= '-' | ['K'] ['Q'] ['k'] ['q'] (1..4)

<En passant target square> ::= '-' | <epsquare>
<epsquare>   ::= <fileLetter> <eprank>
<fileLetter> ::= 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h'
<eprank>     ::= '3' | '6'

<Halfmove Clock> ::= <digit> {<digit>}
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

<Fullmove counter> ::= <digit19> {<digit>}
<digit19> ::= '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
<digit>   ::= '0' | <digit19>


*/

#include "constants.h"
#include <string>

typedef struct{
	/* Piece bit boards */
	uint64_t pieces[NUM_BITBOARDS];
	/* Side to move */
	Color side;
	/* Castling ability */
	bool castle_ability[4];
	/* En Passant Target Square */
	Square en_passant_target;
	/* Half Move Clock */
	int half_moves;
	/* Full Move Counter */
	int num_moves;
} Fen;

/* ---- FEN PARSER ---- */
// parses a fen string into a Fen object
// returns nullptr on failure
Fen* parseFenString(std::string fen_string);
bool isValidFenString(std::string fen_string);

void testFen();

#endif //FEN_H