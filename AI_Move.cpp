#include "AI_Move.h"

namespace c_4 {
	int makeMove(Piece piece, Board& board, int difficulty){
		int max = 0;
		int answer = maximizer(board, piece, difficulty + 1);
		Piece other = otherPiece(piece);
		int cols[7];
		Board boards[7];
		for (int i = 0; i < 7; i++) {
			cols[i] = 0;
			boards[i] = board.cloneBoard();
		}
		for (int i = 0; i < 7; i++) {
			if (board.isValidMove(i)) {
				boards[i].placePiece(piece, i);
				cols[i] = minimizer(boards[i], other, difficulty);
			}
		}
		for (int i = 0; i < 7; i++) {
			if (cols[i] > max) {
				max = cols[i];
				answer = i;
			}
		}
		return answer;
	}
	int minimizer(Board& board, Piece piece, int depth) {
		int answer = 0;
		Piece other = otherPiece(piece);
		if (board.isWinner() == Piece::Empty) {
			if (depth > 0) {
				int cols[7];
				Board boards[7];
				for (int i = 0; i < 7; i++) {
					cols[i] = 0;
					boards[i] = board.cloneBoard();
				}
				for (int i = 0; i < 7; i++) {
					if (board.isValidMove(i)) {
						boards[i].placePiece(piece, i);
						cols[i] = maximizer(boards[i], other, depth - 1);
					}
				}
				for (int i = 0; i < 7; i++) {
					if (cols[i] < answer) {
						answer = cols[i];
					}
				}
			}
			else {
				answer = heuristic(board, other);
			}
		}
		else {
			if (board.isWinner() == piece) {
				answer = -100;
			}
			else {
				answer = 100;
			}
		}
		return answer;
	}
	int maximizer(Board& board, Piece piece, int depth) {
		int answer = 0;
		Piece other = otherPiece(piece);
		if (board.isWinner() == Piece::Empty){
			if (depth > 0) {
				int cols[7];
				Board boards[7];
				for (int i = 0; i < 7; i++) {
					cols[i] = 0;
					boards[i] = board.cloneBoard();
				}
				for (int i = 0; i < 7; i++) {
					if (board.isValidMove(i)) {
						boards[i].placePiece(piece, i);
						cols[i] = minimizer(boards[i], other, depth - 1);
					}
				}
				for (int i = 0; i < 7; i++) {
					if (cols[i] > answer) {
						answer = cols[i];
					}
				}
			}
			else {
				answer = heuristic(board, piece);
			}
		}
		else {
			if (board.isWinner() == piece) {
				answer = 100;
			}
			else {
				answer = -100;
			}
		}
		return answer;
	}
	int heuristic(Board& board, Piece piece) {
		int answer = 0;
		if (board.isWinner() == piece) {
			answer = 100;
		}
		else if (board.isWinner() == otherPiece(piece)){
			answer = -100;
		}
		else if (oneAway(board, piece)) {
			answer = 30;
		}
		else if (oneAway(board, otherPiece(piece))) {
			answer = -30;
		}
		else if (twoAway(board, piece)) {
			answer = 5;
		}
		else if (twoAway(board, otherPiece(piece))) {
			answer = -5;
		}
		return answer;
	}
	bool oneAway(Board& board, Piece piece) {
		bool answer = false;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				int inARow = 1;
				Piece checkPiece = board.getLocation(i, j);
				if (checkPiece == piece) {
					bool blocked;
					int inARow;
					if (board.isRowValid(i, j, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isRowValid(i, j, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isColValid(i, j, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isColValid(i, j, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Positive, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Positive, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Negative, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Negative, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 2 && !blocked) {
							answer = true;
						}
					}
				}
			}
		}
		return answer;
	}
	bool twoAway(Board& board, Piece piece) {
		bool answer = false;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				int inARow = 1;
				Piece checkPiece = board.getLocation(i, j);
				if (checkPiece == piece) {
					bool blocked;
					int inARow;
					if (board.isRowValid(i, j, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isRowValid(i, j, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isColValid(i, j, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isColValid(i, j, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Positive, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Positive, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i + k, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i + k, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Negative, Dir::Positive)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j + k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j + k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
					if (board.isDiagValid(i, j, Dir::Negative, Dir::Negative)) {
						blocked = false;
						inARow = 1;
						for (int k = 1; k < 4; k++) {
							if (board.getLocation(i - k, j - k) == checkPiece) {
								inARow++;
							}
							else if (board.getLocation(i - k, j - k) == otherPiece(checkPiece)) {
								blocked = true;
							}
						}
						if (inARow > 1 && !blocked) {
							answer = true;
						}
					}
				}
			}
		}
		return answer;
	}
	Piece otherPiece(Piece piece) {
		Piece other;
		if (piece == Piece::Blue) {
			other = Piece::Red;
		}
		else {
			other = Piece::Blue;
		}
		return other;
	}

}