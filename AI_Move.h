#pragma once
#include "board.h"

namespace c_4 {
	int makeMove(Piece piece, Board& board, int difficulty);
	int minimizer(Board& board, Piece piece, int depth);
	int maximizer(Board& board, Piece piece, int depth);
	int heuristic(Board& board, Piece piece);
	bool oneAway(Board& board, Piece piece);
	bool twoAway(Board& board, Piece piece);
	Piece otherPiece(Piece piece);
}