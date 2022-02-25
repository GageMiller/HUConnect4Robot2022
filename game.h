#pragma once
#include "board.h"

namespace c_4 {
	class Game {
	private:
		Board board;
	public:
		void placeMove(Piece piece, int column);
		bool isGameFinished(Piece& result);
		Board& currentBoard();
	};
}