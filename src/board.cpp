//
//  board.cpp
//  My Engine
//
//  Created by Nikhil Arora on 9/22/2021.
//  Copyright © 2021 Nikhil Arora. All rights reserved.
//

#include "board.h"
#include <iostream>
#include <fcntl.h>
#include "bitops.h"
#include "fen.h"

#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"

/* ---- BOARD CONSTRUCTORS ---- */

// default constructor
Board::Board(){
	m_pieces[(nAll << 1) + nWhite]     = WHITE_PIECES_START;
	m_pieces[(nAll << 1) + nBlack]     = BLACK_PIECES_START;
	m_pieces[(nPawn << 1) + nWhite]    = WHITE_PAWN_START;
	m_pieces[(nPawn << 1) + nBlack]    = BLACK_PAWN_START;
	m_pieces[(nKnight << 1) + nWhite]  = WHITE_KNIGHT_START;
	m_pieces[(nKnight << 1) + nBlack]  = BLACK_KNIGHT_START;
	m_pieces[(nBishop << 1) + nWhite]  = WHITE_BISHOP_START;
	m_pieces[(nBishop << 1) + nBlack]  = BLACK_BISHOP_START;
	m_pieces[(nRook << 1) + nWhite]    = WHITE_ROOK_START;
	m_pieces[(nRook << 1) + nBlack]    = BLACK_ROOK_START;
	m_pieces[(nQueen << 1) + nWhite]   = WHITE_QUEEN_START;
	m_pieces[(nQueen << 1) + nBlack]   = BLACK_QUEEN_START;
	m_pieces[(nKing << 1) + nWhite]    = WHITE_KING_START;
	m_pieces[(nKing << 1) + nBlack]    = BLACK_KING_START;
	m_side = nWhite;
	m_castle_ability[0] = true;
	m_castle_ability[1] = true;
	m_castle_ability[2] = true;
	m_castle_ability[3] = true;
	m_en_passant_target = none;
	m_half_moves = 0;
	m_num_moves = 1;
}

// construct board from bit board array
Board::Board(uint64_t pieces[NUM_BITBOARDS], Color side, 
	         bool castle_ability[4], Square en_passant_target, 
	         int half_moves, int num_moves){
	for(int i = 0; i < NUM_BITBOARDS; i++){
		m_pieces[i] = pieces[i];
	}
	m_side = side;
	m_castle_ability[0] = castle_ability[0];
	m_castle_ability[1] = castle_ability[1];
	m_castle_ability[2] = castle_ability[2];
	m_castle_ability[3] = castle_ability[3];
	m_en_passant_target = en_passant_target;
	m_half_moves = half_moves;
	m_num_moves = num_moves;
}

// copy constructor
Board::Board(const Board& other){
	m_side = other.m_side;
	m_castle_ability[0] = other.m_castle_ability[0];
	m_castle_ability[1] = other.m_castle_ability[1];
	m_castle_ability[2] = other.m_castle_ability[2];
	m_castle_ability[3] = other.m_castle_ability[3];
	m_en_passant_target = other.m_en_passant_target;
	m_half_moves = other.m_half_moves;
	m_num_moves = other.m_num_moves;
	for(int i = 0; i < NUM_BITBOARDS; i++){
		m_pieces[i] = other.m_pieces[i];
	}
}

// FEN string constructor
Board::Board(const std::string& FEN){
	Fen* f = parseFenString(FEN);
	if(f != nullptr){
		for(int i = 0; i < NUM_BITBOARDS; i++)
			m_pieces[i] = f->pieces[i];
		m_side = f->side;
		m_castle_ability[0] = f->castle_ability[0];
		m_castle_ability[1] = f->castle_ability[1];
		m_castle_ability[2] = f->castle_ability[2];
		m_castle_ability[3] = f->castle_ability[3];
		m_en_passant_target = f->en_passant_target;
		m_half_moves = f->half_moves;
		m_num_moves = f->num_moves;
		delete f;
	}
	else{
		std::cerr << "Error: unable to construct Board object from FEN string" << std::endl;
		exit(EXIT_FAILURE);
	}
}



/* ---- BIT BOARD GETTERS ---- */

// functions that get the piece and color bit boards 
// returns a bit board for a certain piece and color
uint64_t Board::getPieceBitBoard(Piece p, Color c) const{
	return m_pieces[(p << 1) + c];
}
uint64_t Board::getPieceBitBoard(int bitboard_index) const{
	return m_pieces[bitboard_index];
}
// returns bit board for all pieces on the board
uint64_t Board::getAllPieces() const{
	return m_pieces[WHITE_ALL_PIECES_BB] | m_pieces[BLACK_ALL_PIECES_BB];
}
// returns bit board for all empty squares on the board
uint64_t Board::getEmptySquares() const{
	return ~(m_pieces[WHITE_ALL_PIECES_BB] | m_pieces[BLACK_ALL_PIECES_BB]);
}
// returns bit board for all pieces of the same color
uint64_t Board::getAllColorPieces(Color c) const{
	return m_pieces[(nAll << 1) + c];
}
// following functions return piece set of each piece for a given color
uint64_t Board::getPawns(Color c) const{
	return m_pieces[(nPawn << 1) + c];
}
uint64_t Board::getKnights(Color c) const{
	return m_pieces[(nKnight << 1) + c];
}
uint64_t Board::getBishops(Color c) const{
	return m_pieces[(nBishop << 1) + c];
}
uint64_t Board::getRooks(Color c) const{
	return m_pieces[(nRook << 1) + c];
}
uint64_t Board::getQueen(Color c) const{
	return m_pieces[(nQueen << 1) + c];
}
uint64_t Board::getKing(Color c) const{
	return m_pieces[(nKing << 1) + c];
}



/* ---- OTHER GETTERS ---- */
Color Board::getSideToMove() const{
	return m_side;
}
bool Board::getCastleAbility(int castle_side) const{
	if(castle_side >= 0 && castle_side < 4)
		return m_castle_ability[castle_side];
	return false;
}
Square Board::getEnPassantTarget() const{
	return m_en_passant_target;
}
int Board::getHalfMoves() const{
	return m_half_moves;
}
int Board::getNumMoves() const{
	return m_num_moves;
}


/* ---- SQUARE ATTACKED BY ---- */
uint64_t Board::attacksTo(Square sq) const{
	uint64_t occupied = m_pieces[WHITE_ALL_PIECES_BB] | m_pieces[BLACK_ALL_PIECES_BB];
	uint64_t knights, kings, bishopsQueens, rooksQueens;
	knights = m_pieces[WHITE_KNIGHTS_BB] | m_pieces[BLACK_KNIGHTS_BB];
	kings = m_pieces[WHITE_KING_BB] | m_pieces[BLACK_KING_BB];
	rooksQueens = bishopsQueens = m_pieces[WHITE_QUEEN_BB] | m_pieces[BLACK_QUEEN_BB];
	rooksQueens |= m_pieces[WHITE_ROOKS_BB] | m_pieces[BLACK_ROOKS_BB];
	bishopsQueens |= m_pieces[WHITE_BISHOPS_BB] | m_pieces[BLACK_BISHOPS_BB];
	return (lookupPawnAttacks(sq, nWhite) & m_pieces[BLACK_PAWNS_BB])
		| (lookupPawnAttacks(sq, nBlack) & m_pieces[WHITE_PAWNS_BB])
		| (lookupKnightAttacks(sq) & knights)
		| (lookupKingAttacks(sq) & kings)
		| (lookupBishopAttacks(sq, occupied) & bishopsQueens)
		| (lookupRookAttacks(sq, occupied) & rooksQueens);
}
bool Board::attacked(Square sq, Color attacker) const{
	uint64_t occupied = m_pieces[WHITE_ALL_PIECES_BB] | m_pieces[BLACK_ALL_PIECES_BB];
	uint64_t pawns = m_pieces[(nPawn << 1) + attacker];
	if(lookupPawnAttacks(sq, (Color)(attacker ^ 1)) & pawns)
		return true;
	uint64_t knights = m_pieces[(nKnight << 1) + attacker];
	if(lookupKnightAttacks(sq) & knights)
		return true;
	uint64_t king = m_pieces[(nKing << 1) + attacker];
	if(lookupKingAttacks(sq) & king)
		return true;
	uint64_t bishopsQueens = m_pieces[(nBishop << 1) + attacker] 
						   | m_pieces[(nQueen << 1) + attacker];
	if(lookupBishopAttacks(sq, occupied) & bishopsQueens)
		return true;
	uint64_t rooksQueens = m_pieces[(nRook << 1) + attacker]
						   | m_pieces[(nQueen << 1) + attacker];
	if(lookupRookAttacks(sq, occupied) & rooksQueens)
		return true;
	return false;
}
bool Board::inCheck(Color c) const{
	return attacked((Square)getLS1bIndex(m_pieces[(nKing << 1) + c]), (Color)(c ^ 1));
}


/* ---- MAKE MOVES ---- */
// makes move regardless of legality
void Board::makeMove(Move m){
	unsigned int toSquare = m.getToSquare();
	unsigned int fromSquare = m.getFromSquare();
	uint64_t toMask = 1ULL << toSquare;
	uint64_t fromMask = 1ULL << fromSquare;
	Color opponent = (Color)(m_side ^ 1);
	// Exit if there is no piece to move
	if((m_pieces[(nAll << 1) + m_side] & fromMask) == 0)
		return;

	// Fetch moved piece and move it
	Piece movedPiece = nAll;
	for(int i = 1; i <= NUM_PIECES; i++){
		// update moved piece
		if((m_pieces[WHITE_ALL_PIECES_BB + 2*i + m_side] & fromMask) != 0){
			movedPiece = (Piece) i;
			m_pieces[WHITE_ALL_PIECES_BB + 2*i + m_side] &= ~fromMask;
			m_pieces[WHITE_ALL_PIECES_BB + 2*i + m_side] |= toMask;
			m_pieces[WHITE_ALL_PIECES_BB + m_side] &= ~fromMask;
			m_pieces[WHITE_ALL_PIECES_BB + m_side] |= toMask;
		}
		// erase captured pieces
		if(m.isCapture()){
			if((m_pieces[WHITE_ALL_PIECES_BB + 2*i + opponent] & toMask) != 0){
				m_pieces[WHITE_ALL_PIECES_BB + 2*i + opponent] &= ~toMask;
				m_pieces[WHITE_ALL_PIECES_BB + opponent] &= ~toMask;
			}
		}
	}

	// Add promoted piece
	if(m.isPromotion()){
		Piece promo = m.promotionType();
		// remove 1st or 8th rank pawn
		m_pieces[(nPawn << 1) + m_side] &= ~toMask;
		// add new piece
		m_pieces[(promo << 1) + m_side] |= toMask;
	}

	// Remove en passant captured pawn
	if(m.isEnPassant()){
		int shift = opponent == nWhite? 8: -8;
		uint64_t epMask = (1ULL << (m_en_passant_target + shift));
		m_pieces[(nPawn << 1) + opponent] &= ~epMask;
		m_pieces[(nAll << 1) + opponent] &= ~epMask;
	}

	// move rook in case of castling
	if(m.isKingSideCastle()){
		if(m_side == nWhite){
			m_pieces[WHITE_ROOKS_BB] &= ~(1ULL << h1);
			m_pieces[WHITE_ALL_PIECES_BB] &= ~(1ULL << h1);
			m_pieces[WHITE_ROOKS_BB] |= (1ULL << f1);
			m_pieces[WHITE_ALL_PIECES_BB] |= (1ULL << f1);
		}
		else{
			m_pieces[BLACK_ROOKS_BB] &= ~(1ULL << h8);
			m_pieces[BLACK_ALL_PIECES_BB] &= ~(1ULL << h8);
			m_pieces[BLACK_ROOKS_BB] |= (1ULL << f8);
			m_pieces[BLACK_ALL_PIECES_BB] |= (1ULL << f8);
		}
	}
	else if(m.isQueenSideCastle()){
		if(m_side == nWhite){
			m_pieces[WHITE_ROOKS_BB] &= ~(1ULL << a1);
			m_pieces[WHITE_ALL_PIECES_BB] &= ~(1ULL << a1);
			m_pieces[WHITE_ROOKS_BB] |= (1ULL << d1);
			m_pieces[WHITE_ALL_PIECES_BB] |= (1ULL << d1);
		}
		else{
			m_pieces[BLACK_ROOKS_BB] &= ~(1ULL << a8);
			m_pieces[BLACK_ALL_PIECES_BB] &= ~(1ULL << a8);
			m_pieces[BLACK_ROOKS_BB] |= (1ULL << d8);
			m_pieces[BLACK_ALL_PIECES_BB] |= (1ULL << d8);
		}
	}

	// Update castling rights (if rook is moved/captured or king moves)
	if(movedPiece == nKing){
		m_castle_ability[2*m_side] = false;
		m_castle_ability[2*m_side + 1] = false;
	}
	if(((1ULL << a1) & m_pieces[WHITE_ROOKS_BB]) == 0)
		m_castle_ability[WHITE_QUEEN_SIDE_CASTLE] = false;
	if(((1ULL << h1) & m_pieces[WHITE_ROOKS_BB]) == 0)
		m_castle_ability[WHITE_KING_SIDE_CASTLE] = false;
	if(((1ULL << a8) & m_pieces[BLACK_ROOKS_BB]) == 0)
		m_castle_ability[BLACK_QUEEN_SIDE_CASTLE] = false;
	if(((1ULL << h8) & m_pieces[BLACK_ROOKS_BB]) == 0)
		m_castle_ability[BLACK_KING_SIDE_CASTLE] = false;

	// Set en passant target
	if(m.isDoublePawnPush()){
		if(m_side == nWhite){
			m_en_passant_target = (Square)(toSquare - 8);
		}
		else{
			m_en_passant_target = (Square)(toSquare + 8);
		}
	}
	else
		m_en_passant_target = none;

	// Increment or reset half move clock counter
	if(m.isCapture() || movedPiece == nPawn)
		m_half_moves = 0;
	else
		m_half_moves++;

	// Increment num_moves if black just moved
	if(m_side == nBlack)
		m_num_moves++;

	// Toggle side to move
	m_side = opponent;
	printMembers();
}
unsigned int stringToSquare(std::string s){
	unsigned int file = s[0] - 'a';
	unsigned int rank = s[1] - '1';
	return file + 8*rank;
}
void Board::testMakeMove(){
	while(true){
		printBoard();
		std::string a, b;
		std::cout << "Square to move from: ";
		std::cin >> a;
		std::cout << std::endl << "Square to move to: ";
		std::cin >> b;

		unsigned int to, from, flags;
		to = stringToSquare(b);
		from = stringToSquare(a);
		std::cout << std::endl << "Flags: ";
		std::cin >> flags;
		Move m(to, from, flags);
		makeMove(m);
	}
}


/* ---- PRINT FUNCTIONS ---- */
// print functions useful for debugging

// prints the whole board
void Board::printBoard() const{
	printBoard(getAllPieces());
}
// prints a given bit board according to the game state represented by this board
void Board::printBoard(const uint64_t& b) const{
	char board[NUM_RANKS][NUM_FILES];
	uint64_t bitmask = 1;
	for(int i = 0 ; i < NUM_RANKS; i++){
		for(int j = 0; j < NUM_FILES; j++){
			bool occupied = false;
			for(int p = nPawn; p <= nKing; p++){
				for(int c = nWhite; c <= nBlack; c++){
					if((bitmask & b & getPieceBitBoard((Piece)p, (Color)c)) != 0){
						board[i][j] = getPieceChar((Piece)p, (Color)c);
						occupied = true;
						break;
					}
				}
				if(occupied)
					break;
			}
			if(!occupied)
				board[i][j] = EMPTY_CHAR;
			bitmask = bitmask << 1;
		}
	}
	printBoardArray(board);
}
// prints all pieces of one color
void Board::printColorBitBoard(Color c) const{
	printBoard(getAllColorPieces(c));
}
// prints all pieces of one piece type and one color
void Board::printPieceBitBoard(Piece p, Color c) const{
	printBoard(getPieceBitBoard(p, c));
}
// prints every bit board
void Board::printAllBitBoards() const{
	for(int p = nAll; p <= nKing; p++){
		printPieceBitBoard((Piece)p, nWhite);
		std::cout << std::endl;
		printPieceBitBoard((Piece)p, nBlack);
		std::cout << std::endl;
	}
	printBoard();
}
// prints private member variables
void Board::printMembers() const{
	std::string side = m_side == nWhite ? "White" : "Black";
	std::cout << "Side to play: " << side << std::endl;
	std::cout << "En Passantable square: " << m_en_passant_target << std::endl;
	std::cout << "Half move clock: " << m_half_moves << std::endl;
	std::cout << "Number of moves: " << m_num_moves << std::endl;
	std::cout << "White king side castling ability: " << m_castle_ability[WHITE_KING_SIDE_CASTLE] << std::endl;
	std::cout << "White queen side castling ability: " << m_castle_ability[WHITE_QUEEN_SIDE_CASTLE] << std::endl;
	std::cout << "Black king side castling ability: " << m_castle_ability[BLACK_KING_SIDE_CASTLE] << std::endl;
	std::cout << "Black queen side castling ability: " << m_castle_ability[BLACK_QUEEN_SIDE_CASTLE] << std::endl;
}

// private helper print functions
// gets character representing a piece of a color
char Board::getPieceChar(Piece p, Color c) const{
	char pieceChar = '1';
	// use ascii characters to represent pieces
	if(c == nWhite){
		switch(p){
			case nPawn: pieceChar = WHITE_PAWN_CHAR; break;
			case nKnight: pieceChar = WHITE_KNIGHT_CHAR; break;
			case nBishop: pieceChar = WHITE_BISHOP_CHAR; break;
			case nRook: pieceChar = WHITE_ROOK_CHAR; break;
			case nQueen: pieceChar = WHITE_QUEEN_CHAR; break;
			case nKing: pieceChar = WHITE_KING_CHAR; break;
			default: pieceChar = EMPTY_CHAR;
		}
	}
	else if(c == nBlack){
		switch(p){
			case nPawn: pieceChar = BLACK_PAWN_CHAR; break;
			case nKnight: pieceChar = BLACK_KNIGHT_CHAR; break;
			case nBishop: pieceChar = BLACK_BISHOP_CHAR; break;
			case nRook: pieceChar = BLACK_ROOK_CHAR; break;
			case nQueen: pieceChar = BLACK_QUEEN_CHAR; break;
			case nKing: pieceChar = BLACK_KING_CHAR; break;
			default: pieceChar = EMPTY_CHAR;
		}
	}
	return pieceChar;
}
// prints board array
void Board::printBoardArray(char board[NUM_RANKS][NUM_FILES]) const{
	std::string border = "+---+---+---+---+---+---+---+---+";
	std::cout << border << std::endl;
	for(int i = NUM_RANKS - 1; i >= 0; i--){
		std::cout << "| ";
		for(int j = 0; j < NUM_FILES; j++){
			std::cout << board[i][j];
			std::cout << " | ";
		}
		std::cout << std::endl << border << std::endl;
	}	
}