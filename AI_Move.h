#pragma once
#include "board.h"
#include <array>
#include <stdio.h>
#include <vector>

namespace c_4 {
	void makeMove(Board& b, int c, Piece p);
	bool winningMove(Board& b, Piece p);
	int scoreSet(std::vector<Piece> v, Piece p);
	int tabScore(Board b, Piece p);
	std::array<int, 2> miniMax(Board& b, int d, int alf, int bet, Piece p);
	int heurFunction(unsigned int, unsigned int, unsigned int);
	Piece otherPiece(Piece piece);
}