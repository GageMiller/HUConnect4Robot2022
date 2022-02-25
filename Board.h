#pragma once
#include <array>
namespace c_4 {
	enum class Piece { Red, Blue, Empty };
	using Grid = std::array<std::array<Piece, 7>, 6>;
	enum class Dir {Positive, Negative};
	enum class Turn { Player, AI };
	class Board {
	private:
		Grid _grid;
		int _numOfPieces;
	public:
		Board();
		Board(Grid grid, int numOfPieces);
		bool isValidLocation(int row, int col);
		bool isRowValid(int row, int col, Dir dir);
		bool isColValid(int row, int col, Dir dir);
		bool isDiagValid(int row, int col, Dir rowDir, Dir colDir);
		Piece getLocation(int row, int col);
		void placePiece(Piece piece, int column);
		bool isValidMove(int col);
		bool isBoardFull();
		Piece isWinner();
		Board cloneBoard();
	};
	
}