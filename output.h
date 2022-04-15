#pragma once
#include "board.h"
#include <iostream>
#include <string>

namespace c_4 {
	void welcome(std::ostream& out);
	void displayBoard(std::ostream& out, Board board);
	void askForMove(std::ostream& out);
	void printMove(int col, std::ostream& out);
	void returnGameResult(GameResult result, std::ostream& out, Board board);
	void askForDifficulty(std::ostream& out);
	void askForTurn(std::ostream& out);
	void askIfContinuing(std::ostream& out);
	void end(std::ostream& out);
}
