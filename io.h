#pragma once
#include "board.h"
#include <iostream>
#include <string>

namespace c_4 {
	enum class GameResult {
		Win,
		Lose,
		Full
	};

	void welcome(std::ostream& out);
	void displayBoard(std::ostream& out, Board board);
	void askForMove(std::ostream& out);
	int getMove(std::istream& in);
	void printMove(int col, std::ostream& out);
	void returnGameResult(GameResult result, std::ostream& out, Board board);
	int getDifficulty(std::ostream& out, std::istream& in);
	Turn getTurn(std::ostream& out, std::istream& in);
	bool isContinuing(std::ostream& out, std::istream& in);
	void end(std::ostream& out);
}