#include "output.h"
namespace c_4 {
	void welcome(std::ostream& out) {
		out << "Welcome to Connect 4" << std::endl;
	}
	void displayBoard(std::ostream& out, Board board) {
		for (int i = 5; i >= 0; i--) {
			out << "|";
			for (int j = 0; j < 7; j++) {
				Piece myPiece = board.getLocation(i, j);
				if (myPiece == Piece::Blue)
					out << "B";
				else if (myPiece == Piece::Red)
					out << "R";
				else
					out << "O";
				out << "|";
			}
			out << std::endl;
		}
	}
	void askForMove(std::ostream& out) {
		out << "Where would you like to move? ";
	}
	void printMove(int col, std::ostream& out) {
		out << "Placed piece in column " << col + 1 << "." << std::endl;
	}
	void returnGameResult(GameResult result, std::ostream& out, Board board) {
		out << std::endl << "***Game Over***" << std::endl;
		displayBoard(out, board);
		if (result == GameResult::Win) {
			out << "Congratulations, You win" << std::endl;
		}
		else if (result == GameResult::Lose) {
			out << "Better Luck next time" << std::endl;
		}
		else {
			out << "Looks like it's a tie..." << std::endl;
		}
	}
	void askForDifficulty(std::ostream& out){
		out << "What difficulty would you like to play? ";
	}
	void askForTurn(std::ostream& out){
		out << "Would you like to go [1]st or [2]nd? ";
	}
	void askIfContinuing(std::ostream& out){
		out << "Would you like to play again? ";
	}
	void end(std::ostream& out) {
		out << "Thank you for playing Connect 4" << std::endl;
	}
}