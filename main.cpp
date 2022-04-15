#include "game.h"
#include "input.h"
#include "output.h"
#include "getMove.h"
#include "AI_Move.h"
#include "Board.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace c_4;

void main() {
	bool quit = false;
	int difficulty;
	welcome(cout);
	while (!quit) {
		askForDifficulty(cout);
		difficulty = getDifficulty(cin);
		Game game;
		GameResult result;
		Piece winner;
		askForTurn(cout);
		Turn turn = getTurn(cin);
		string response;
		int move;
		displayBoard(cout, game.currentBoard());
		while (!game.isGameFinished(winner)) {
			if (turn == Turn::Player) {
				askForMove(cout);
				move = getMove(cin);
				move--;
				game.placeMove(Piece::Red, move);
				turn = Turn::AI;
				cout << "You ";
			}
			else {
				move = makeMove(Piece::Blue, game.currentBoard(), difficulty);
				//Two player code
				//askForMove(cout);
				//move = getMove(cin);
				//move--;
				game.placeMove(Piece::Blue, move);
				turn = Turn::Player;
				cout << "AI ";
			}
			printMove(move, cout);
			displayBoard(cout, game.currentBoard());
		}
		if (winner == Piece::Empty) {
			result = GameResult::Full;
		}
		else if (winner == Piece::Red) {
			result = GameResult::Win;
		}
		else {
			result = GameResult::Lose;
		}
		returnGameResult(result, cout, game.currentBoard());
		askIfContinuing(cout);
		if (!isContinuing(cin)) {
			quit = true;
		}
	}
	end(cout);
}