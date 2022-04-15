#include "game.h"
#include "input.h"
#include "output.h"
#include "getMove.h"
#include "AI_Move.h"
#include "Board.h"
#include "Hardware.h"
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
		returnDropper();
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
				move = miniMax(game.currentBoard(), difficulty, 0 - INT_MAX, INT_MAX, Piece::Blue)[1];
				//Two player code
				//askForMove(cout);
				//move = getMove(cin);
				//move--;
				game.placeMove(Piece::Blue, move);
				positionDropper(move);
				dropPiece();
				returnDropper();
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