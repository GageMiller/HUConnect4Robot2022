#include "Board.h"

namespace c_4 {
	Board::Board(){
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				_grid[i][j] = Piece::Empty;
			}
		}
		_numOfPieces = 0;
	}
	Board::Board(Grid grid, int numOfPieces){
		_grid = grid;
		_numOfPieces = numOfPieces;
	}
	Piece Board::getLocation(int row, int col){
		return _grid[row][col];
	}
	void Board::placePiece(Piece piece, int column) {
		bool isPlaced = false;
		if (isValidMove(column)) {
			for (int i = 0; i < 6 && !isPlaced; i++) {
				if (_grid[i][column] == Piece::Empty) {
					isPlaced = true;
					_grid[i][column] = piece;
				}
			}
		}
		_numOfPieces++;
	}
	bool Board::isValidMove(int col){
		bool answer = false;
		for (int i = 0; i < 6; i++) {
			if (_grid[i][col] == Piece::Empty) {
				answer = true;
			}
		}
		return answer;
	}
	bool Board::isBoardFull(){
		return _numOfPieces==42;
	}
	bool Board::isValidLocation(int row, int col) {
		return !((row > 5) || (row < 0) || (col > 6) || (col < 0));		
	}
	bool Board::isRowValid(int row, int col, Dir dir) {
		bool answer = true;
		int multiplier = 1;
		if (dir == Dir::Negative) {
			multiplier = -1;
		}
		for (int i = 0; i < 4; i++) {
			if (!isValidLocation(row, col + i*multiplier)) {
				answer = false;
			}
		}
		return answer;
	}
	bool Board::isColValid(int row, int col, Dir dir){
		bool answer = true;
		int multiplier = 1;
		if (dir == Dir::Negative) {
			multiplier = -1;
		}
		for (int i = 0; i < 4; i++) {
			if (!isValidLocation(row + i * multiplier, col)) {
				answer = false;
			}
		}
		return answer;
	}
	bool Board::isDiagValid(int row, int col,Dir rowDir , Dir colDir){
		bool answer = true;
		int rowMultiplier = 1;
		int colMultiplier = 1;
		if (rowDir == Dir::Negative) {
			rowMultiplier = -1;
		}
		if (colDir == Dir::Negative) {
			colMultiplier = -1;
		}
		for (int i = 0; i < 4; i++) {
			if (!isValidLocation(row + i*rowMultiplier, col + i * colMultiplier)) {
				answer = false;
			}
		}
		return answer;
	}
	Piece Board::isWinner() {
		Piece answer = Piece::Empty;
		Piece checkPiece;
		for (int i = 0; i < 6 && answer == Piece::Empty; i++) {
			for (int j = 0; j < 7 && answer == Piece::Empty; j++) {
				checkPiece = _grid[i][j];
				if (checkPiece != Piece::Empty) {
					if (isRowValid(i,j,Dir::Positive)) {
						if ((_grid[i][j + 1] == checkPiece) && (_grid[i][j+2] == checkPiece) && (_grid[i][j+3] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isRowValid(i, j, Dir::Negative)) {
						if ((_grid[i][j - 1] == checkPiece) && (_grid[i][j - 2] == checkPiece) && (_grid[i][j - 3] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isColValid(i, j, Dir::Positive)) {
						if ((_grid[i + 1][j] == checkPiece) && (_grid[i + 2][j] == checkPiece) && (_grid[i + 3][j] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isColValid(i, j, Dir::Negative)) {
						if ((_grid[i - 1][j] == checkPiece) && (_grid[i - 2][j] == checkPiece) && (_grid[i - 3][j] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isDiagValid(i, j, Dir::Positive, Dir::Positive)) {
						if ((_grid[i + 1][j + 1] == checkPiece) && (_grid[i + 2][j + 2] == checkPiece) && (_grid[i + 3][j + 3] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isDiagValid(i, j, Dir::Positive, Dir::Negative)) {
						if ((_grid[i + 1][j - 1] == checkPiece) && (_grid[i + 2][j - 2] == checkPiece) && (_grid[i + 3][j - 3] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isDiagValid(i, j, Dir::Negative, Dir::Positive)) {
						if ((_grid[i - 1][j + 1] == checkPiece) && (_grid[i - 2][j + 2] == checkPiece) && (_grid[i - 3][j + 3] == checkPiece)) {
							answer = checkPiece;
						}
					}
					if (isDiagValid(i, j, Dir::Negative, Dir::Negative)) {
						if ((_grid[i - 1][j - 1] == checkPiece) && (_grid[i - 2][j - 2] == checkPiece) && (_grid[i - 3][j - 3] == checkPiece)) {
							answer = checkPiece;
						}
					}
				}

			}
		}
		return answer;
	}
	Board Board::cloneBoard()
	{
		return Board();
	}
}