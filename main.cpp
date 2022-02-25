#include "game.h"
#include "io.h"
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
		difficulty = getDifficulty(cout, cin);
		Game game;
		GameResult result;
		Piece winner;
		Turn turn = getTurn(cout,cin);
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
		if (!isContinuing(cout, cin)) {
			quit = true;
		}
	}
	end(cout);
}