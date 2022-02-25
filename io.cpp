#include "io.h"

namespace c_4 {
	void welcome(std::ostream& out){
		out << "Welcome to Connect 4" << std::endl;
	}
	void displayBoard(std::ostream& out, Board board){
		for (int i = 5; i >=0; i--) {
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
	void askForMove(std::ostream& out){
		out << "Where would you like to move? ";
	}
	int getMove(std::istream& in){
		int answer;
		in >> answer;
		return answer;
	}
	void printMove(int col, std::ostream& out){
		out << "Placed piece in column " << col+1 << "." << std::endl;
	}
	void returnGameResult(GameResult result, std::ostream& out, Board board){
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
	int getDifficulty(std::ostream& out, std::istream& in){
		int answer;
		out << "What difficulty would you like to play? ";
		in >> answer;
		return answer;
	}
	Turn getTurn(std::ostream& out, std::istream& in){
		Turn answer;
		std::string response;
		out << "Would you like to go [1]st or [2]nd? ";
		in >> response;
		if (response == "2") {
			answer = Turn::AI;
		}
		else {
			answer = Turn::Player;
		}
		return answer;
	}
	bool isContinuing(std::ostream& out, std::istream& in){
		bool answer = true;
		std::string response;
		out << "Would you like to play again? ";
		in >> response;
		if (response == "no" || response == "No" || response == "NO") {
			answer = false;
		}
		return answer;

	}
	void end(std::ostream& out){
		out << "Thank you for playing Connect 4" << std::endl;
	}
}