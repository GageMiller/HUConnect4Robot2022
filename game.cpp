#include "game.h"

namespace c_4 {
	void Game::placeMove(Piece piece, int column){
		board.placePiece(piece, column);
	}
	bool Game::isGameFinished(Piece& result){
		bool answer = false;
		result = board.isWinner();
		if (result != Piece::Empty) {
			answer = true;
		}
		if (board.isBoardFull()) {
			answer = true;
		}
		return answer;
	}
	Board& Game::currentBoard()
	{
		return board;
	}
}