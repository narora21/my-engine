//
//  fen.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/25/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "fen.h"
#include <iostream>

/* ---- STRUCT VALUES ---- */

/* Rank strings */
std::string ranks[NUM_RANKS];
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

/* ---- GRAMMAR PARSING FUNCTIONS ---- */

std::string fen_to_parse;
char symbol;
size_t index;
bool malformed_input;

// consumes current token and moves onto the next one
void eat(){
	if(index < fen_to_parse.length()){
		symbol = fen_to_parse[index];
		index++;
	}
	else
		symbol = '#'; // end symbol
}

bool isWhiteSpace(char s){
	return (s == ' ' || s == '\t' || s == '\n');
}

bool restIsWhiteSpace(){
	size_t i = index;
	char s = symbol;
	while(isWhiteSpace(s))
		if(i < fen_to_parse.length()){
			s = fen_to_parse[i];
			i++;
		}
		else
			return true;
	return false;
}

void eatWhiteSpace(){
	while(isWhiteSpace(symbol) && index < fen_to_parse.length())
		eat();
}

// symbol accepting function
bool accept(char s){
	if(symbol == s){
		eat();
		return true;
	}
	return false;
}

bool expect(char s){
	if(accept(s)){
		return true;
	}
	malformed_input = true;
	return false;
}

bool isDigit(char s){
	return s >= '0' && s <= '9';
}

bool isWhiteChar(char s){
	return (s == 'P' || s == 'N' || s == 'B' || s == 'R' || s == 'Q' || s == 'K');
}

bool isBlackChar(char s){
	return (s == 'p' || s == 'n' || s == 'b' || s == 'r' || s == 'q' || s == 'k');
}

bool isRankChar(char s){
	return (s >= '0' && s <= '7') || isWhiteChar(s) || isBlackChar(s);
}

bool digit(){
	if(accept('0'))
		;
	else if(accept('1'))
		;
	else if(accept('2'))
		;
	else if(accept('3'))
		;
	else if(accept('4'))
		;
	else if(accept('5'))
		;
	else if(accept('6'))
		;
	else if(accept('7'))
		;
	else if(accept('8'))
		;
	else if(accept('9'))
		;
	else
		return false;
	return true;
}

void digitExpected(){
	if(digit())
		;
	else
		malformed_input = true;
}

void digitOptional(){
	digit();
}

void digit19(){
	if(accept('1'))
		;
	else if(accept('2'))
		;
	else if(accept('3'))
		;
	else if(accept('4'))
		;
	else if(accept('5'))
		;
	else if(accept('6'))
		;
	else if(accept('7'))
		;
	else if(accept('8'))
		;
	else if(accept('9'))
		;
	else
		malformed_input = true;
}

char digit17(){
	if(accept('1'))
		return '1';
	else if(accept('2'))
		return '2';
	else if(accept('3'))
		return '3';
	else if(accept('4'))
		return '4';
	else if(accept('5'))
		return '5';
	else if(accept('6'))
		return '6';
	else if(accept('7'))
		return '7';
	return 0;
}

void fullMove(){
	std::string dig = "";
	if(isDigit(symbol))
		dig += symbol;
	digit19();
	while(isDigit(symbol)){
		dig += symbol;
		digit();
	}
	num_moves = stoi(dig);
}

void halfMove(){
	std::string dig = "";
	if(isDigit(symbol))
		dig += symbol;
	digitExpected();
	while(isDigit(symbol)){
		dig += symbol;
		digit();
	}
	half_moves = stoi(dig);
}

int epLetter(){
	if(accept('a'))
		return 0;
	else if(accept('b'))
		return 1;
	else if(accept('c'))
		return 2;
	else if(accept('d'))
		return 3;
	else if(accept('e'))
		return 4;
	else if(accept('f'))
		return 5;
	else if(accept('g'))
		return 6;
	else if(accept('h'))
		return 7;
	else
		malformed_input = false;
	return -1;
}

int fileRank(){
	if(accept('3'))
		return 3;
	else if(accept('6'))
		return 6;
	else
		malformed_input = true;
	return -1;
}

void epSquare(){
	int file = epLetter();
	int rank = fileRank();
	en_passant_target = (Square) ((8*(rank-1)) + file);
}

void enPassantTarget(){
	if(accept('-'))
		;
	else 
		epSquare();

}

void castlingAbility(){
	if(accept('-'))
		;
	else{
		bool b = false;
		if(accept('K')){
			b = true;
			castle_ability[WHITE_KING_SIDE_CASTLE] = true;
		}
		if(accept('Q')){
			b = true;
			castle_ability[WHITE_QUEEN_SIDE_CASTLE] = true;
		}
		if(accept('k')){
			b = true;
			castle_ability[BLACK_KING_SIDE_CASTLE] = true;
		}
		if(accept('q')){
			b = true;
			castle_ability[BLACK_QUEEN_SIDE_CASTLE] = true;
		}
		if(!b)
			malformed_input = true;
	}
}

void sideToMove(){
	if(accept('w'))
		side = nWhite;
	else if(accept('b'))
		side = nBlack;
	else if(accept('W'))
		side = nWhite;
	else if(accept('B'))
		side = nBlack;
	else
		malformed_input = true;
}

char whitePiece(){
	if(accept('P'))
		return 'P';
	else if(accept('N'))
		return 'N';
	else if(accept('B'))
		return 'B';
	else if(accept('R'))
		return 'R';
	else if(accept('Q'))
		return 'Q';
	else if(accept('K'))
		return 'K';
	return 0;
}

char blackPiece(){
	if(accept('p'))
		return 'p';
	else if(accept('n'))
		return 'n';
	else if(accept('b'))
		return 'b';
	else if(accept('r'))
		return 'r';
	else if(accept('q'))
		return 'q';
	else if(accept('k'))
		return 'k';
	return 0;
}

char piece(){
	char w = whitePiece();
	if(w != 0)
		return w;
	else{
		return blackPiece();
	}
}

void rank(int rank_num){
	std::string rank_str = "";
	if(accept('8'))
		rank_str += '8';
	else{
		while(isRankChar(symbol)){
			char d = digit17();
			if(d != 0)
				rank_str += d;
			char p = piece();
			if(p != 0)
				rank_str += p;
		}
	}
	ranks[rank_num-1] = rank_str;
}

void piecePlacement(){
	rank(8);
	expect('/');
	rank(7);
	expect('/');
	rank(6);
	expect('/');
	rank(5);
	expect('/');
	rank(4);
	expect('/');
	rank(3);
	expect('/');
	rank(2);
	expect('/');
	rank(1);
}

void fen(){
	piecePlacement();
	expect(' ');
	sideToMove();
	expect(' ');
	castlingAbility();
	expect(' ');
	enPassantTarget();
	expect(' ');
	halfMove();
	expect(' ');
	fullMove();
	//eatWhiteSpace();
}


/* ---- BIT BOARD BUILDER ---- */

// Gets index into bitboard array
int bitboardIndex(char p){
	switch(p){
		case 'P': return ((nPawn << 1) + nWhite); break;
		case 'N': return ((nKnight << 1) + nWhite); break;
		case 'B': return ((nBishop << 1) + nWhite); break;
		case 'R': return ((nRook << 1) + nWhite); break;
		case 'Q': return ((nQueen << 1) + nWhite); break;
		case 'K': return ((nKing << 1) + nWhite); break;
		case 'p': return ((nPawn << 1) + nBlack); break;
		case 'n': return ((nKnight << 1) + nBlack); break;
		case 'b': return ((nBishop << 1) + nBlack); break;
		case 'r': return ((nRook << 1) + nBlack); break;
		case 'q': return ((nQueen << 1) + nBlack); break;
		case 'k': return ((nKing << 1) + nBlack); break;
		default: return -1;
	}
}

// Parses board part of FEN string
void parseRanks(){
	for(int i = 0; i < NUM_BITBOARDS; i++)
		pieces[i] = 0;
	uint64_t bitmask = 1;
	for(int i = 0; i < NUM_RANKS; i++){
		std::string rank_str = ranks[i];
		for(size_t j = 0; j < rank_str.length(); j++){
			if(isDigit(rank_str[j])){
				bitmask = bitmask << (rank_str[j] - '0');
			}
			else{
				int k = bitboardIndex(rank_str[j]);
				if(k == -1)
					return; //error
				pieces[k] = pieces[k] | bitmask;
				if(isWhiteChar(rank_str[j]))
					pieces[(nAll << 1) + nWhite] = pieces[(nAll << 1) + nWhite] | bitmask;
				else if(isBlackChar(rank_str[j]))
					pieces[(nAll << 1) + nBlack] = pieces[(nAll << 1) + nBlack] | bitmask;
				bitmask = bitmask << 1;
			}
		}
	}
}


/* ---- FEN PARSER ---- */
// parses a fen string into a Fen object
// returns nullptr on failure
Fen* parseFenString(std::string fen_string){
	fen_to_parse = fen_string;
	if(fen_string.length() < 20)
		return nullptr;
	index = 1;
	symbol = fen_string[0];
	malformed_input = false;
	for(int i = 0; i < 4; i++)
		castle_ability[i] = false;
	fen();
	if(malformed_input)
		return nullptr;
	parseRanks();
	Fen* f = new Fen;
	for(int i = 0; i < NUM_BITBOARDS; i++)
		f->pieces[i] = pieces[i];
	f->side = side;
	for(int i = 0; i < 4; i++)
		f->castle_ability[i] = castle_ability[i];
	f->en_passant_target = en_passant_target;
	f->half_moves = half_moves;
	f->num_moves = num_moves;
	return f;
}

/* 
//Debugging function 

void testFen(){
	std::string s = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1 ";
	parseFenString(s);
	std::cout << s << std::endl;
	std::cout << "good input: " << !malformed_input << std::endl;
	std::cout << "side to move: " << side << std::endl;
	std::cout << "EP square: " << en_passant_target << std::endl;
	std::cout << "half move: " << half_moves << std::endl;
	std::cout << "full moves: " << num_moves << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << "castling rights: " << i << " " << castle_ability[i] << std::endl;
	std::cout << "Ranks: " << std::endl;
	for(int i = NUM_RANKS-1; i >= 0; i--)
		std::cout << ranks[i] << std::endl;
}
*/
