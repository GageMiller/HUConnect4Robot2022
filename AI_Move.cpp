#include "AI_Move.h"


namespace c_4 {
	#define min(a,b) (((a) < (b)) ? (a) : (b))
	#define max(a,b) (((a) > (b)) ? (a) : (b))
	#define NUM_COL 7
	#define NUM_ROW 6

	/**
	 * Minimax implementation using alpha-beta pruning
	 * param b - the board to perform MM on
	 * param d - the current depth
	 * param alf - alpha
	 * param bet - beta
	 * param p - current player
	 */
	std::array<int, 2> miniMax(Board& b, int d, int alf, int bet, Piece p) {
		/**
		 * if we've reached minimal depth allowed by the program
		 * we need to stop, so force it to return current values
		 * since a move will never (theoretically) get this deep,
		 * the column doesn't matter (-1) but we're more interested
		 * in the score
		 *
		 * as well, we need to take into consideration how many moves
		 * ie when the board is full
		 */
		if (d == 0 || d >= (NUM_COL * NUM_ROW) - b.turns()) {
			// get current score to return
			return std::array<int, 2>{tabScore(b, Piece::Blue), -1};
		}
		if (p == Piece::Blue) { // if AI player
			std::array<int, 2> moveSoFar = { INT_MIN, -1 }; // since maximizing, we want lowest possible value
			if (winningMove(b, Piece::Red)) { // if player about to win
				return moveSoFar; // force it to say it's worst possible score, so it knows to avoid move
			} // otherwise, business as usual
			for (unsigned int c = 0; c < NUM_COL; c++) { // for each possible move
				if (b.getLocation(NUM_ROW - 1,c) == Piece::Empty) { // but only if that column is non-full
					Board newBoard = b.cloneBoard(); // make a copy of the board
					makeMove(newBoard, c, p); // try the move
					int score = miniMax(newBoard, d - 1, alf, bet, Piece::Red)[0]; // find move based on that new board state
					if (score > moveSoFar[0]) { // if better score, replace it, and consider that best move (for now)
						moveSoFar = { score, (int)c };
					}
					alf = max(alf, moveSoFar[0]);
					if (alf >= bet) { break; } // for pruning
				}
			}
			return moveSoFar; // return best possible move
		}
		else {
			std::array<int, 2> moveSoFar = { INT_MAX, -1 }; // since PLAYER is minimized, we want moves that diminish this score
			if (winningMove(b, Piece::Blue)) {
				return moveSoFar; // if about to win, report that move as best
			}
			for (unsigned int c = 0; c < NUM_COL; c++) {
				if (b.getLocation(NUM_ROW - 1,c) == Piece::Empty) {
					Board newBoard = b.cloneBoard();
					makeMove(newBoard, c, p);
					int score = miniMax(newBoard, d - 1, alf, bet, Piece::Blue)[0];
					if (score < moveSoFar[0]) {
						moveSoFar = { score, (int)c };
					}
					bet = min(bet, moveSoFar[0]);
					if (alf >= bet) { break; }
				}
			}
			return moveSoFar;
		}
	}

	Piece otherPiece(Piece piece)
	{
		if (piece == Piece::Blue) {
			return Piece::Red;
		}
		else {
			return Piece::Blue;
		}
	}

	/**
	 * function to tabulate current board "value"
	 * param b - the board to evaluate
	 * param p - the player to check score of
	 * return - the board score
	 */
	int tabScore(Board b, Piece p) {
		int score = 0;
		std::vector<Piece> rs(NUM_COL);
		std::vector<Piece> cs(NUM_ROW);
		std::vector<Piece> set(4);
		/**
		 * horizontal checks, we're looking for sequences of 4
		 * containing any combination of AI, PLAYER, and empty pieces
		 */
		for (unsigned int r = 0; r < NUM_ROW; r++) {
			for (unsigned int c = 0; c < NUM_COL; c++) {
				rs[c] = b.getLocation(r,c); // this is a distinct row alone
			}
			for (unsigned int c = 0; c < NUM_COL - 3; c++) {
				for (int i = 0; i < 4; i++) {
					set[i] = rs[c + i]; // for each possible "set" of 4 spots from that row
				}
				score += scoreSet(set, p); // find score
			}
		}
		// vertical
		for (unsigned int c = 0; c < NUM_COL; c++) {
			for (unsigned int r = 0; r < NUM_ROW; r++) {
				cs[r] = b.getLocation(r,c);
			}
			for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
				for (int i = 0; i < 4; i++) {
					set[i] = cs[r + i];
				}
				score += scoreSet(set, p);
			}
		}
		// diagonals
		for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
			for (unsigned int c = 0; c < NUM_COL; c++) {
				rs[c] = b.getLocation(r,c);
			}
			for (unsigned int c = 0; c < NUM_COL - 3; c++) {
				for (int i = 0; i < 4; i++) {
					set[i] = b.getLocation(r + i,c + i);
				}
				score += scoreSet(set, p);
			}
		}
		for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
			for (unsigned int c = 0; c < NUM_COL; c++) {
				rs[c] = b.getLocation(r,c);
			}
			for (unsigned int c = 0; c < NUM_COL - 3; c++) {
				for (int i = 0; i < 4; i++) {
					set[i] = b.getLocation(r + 3 - i,c + i);
				}
				score += scoreSet(set, p);
			}
		}
		return score;
	}
	/**
	* function that makes the move for the player
	* param b - the board to make move on
	* param c - column to drop piece into
	* param p - the current player
	*/
	void makeMove(Board& b, int c, Piece p) {
		// start from bottom of board going up
		b.placePiece(p, c);
	}
	/**
	 * function to determine if a winning move is made
	 * param b - the board to check
	 * param p - the player to check against
	 * return - whether that player can have a winning move
	 */
	bool winningMove(Board& b, Piece p) {
		unsigned int winSequence = 0; // to count adjacent pieces
		// for horizontal checks
		for (unsigned int c = 0; c < NUM_COL - 3; c++) { // for each column
			for (unsigned int r = 0; r < NUM_ROW; r++) { // each row
				for (int i = 0; i < 4; i++) { // recall you need 4 to win
					if (b.getLocation(r,c + i) == p) { // if not all pieces match
						winSequence++; // add sequence count
					}
					if (winSequence == 4) { return true; } // if 4 in row
				}
				winSequence = 0; // reset counter
			}
		}
		// vertical checks
		for (unsigned int c = 0; c < NUM_COL; c++) {
			for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
				for (int i = 0; i < 4; i++) {
					if (b.getLocation(r + i,c) == p) {
						winSequence++;
					}
					if (winSequence == 4) { return true; }
				}
				winSequence = 0;
			}
		}
		// the below two are diagonal checks
		for (unsigned int c = 0; c < NUM_COL - 3; c++) {
			for (unsigned int r = 3; r < NUM_ROW; r++) {
				for (int i = 0; i < 4; i++) {
					if (b.getLocation(r - i,c + i) == p) {
						winSequence++;
					}
					if (winSequence == 4) { return true; }
				}
				winSequence = 0;
			}
		}
		for (unsigned int c = 0; c < NUM_COL - 3; c++) {
			for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
				for (int i = 0; i < 4; i++) {
					if (b.getLocation(r + i,c + i) == p) {
						winSequence++;
					}
					if (winSequence == 4) { return true; }
				}
				winSequence = 0;
			}
		}
		return false; // otherwise no winning move
	}

	/**
	 * function to find the score of a set of 4 spots
	 * param v - the row/column to check
	 * param p - the player to check against
	 * return - the score of the row/column
	 */
	int scoreSet(std::vector<Piece> v, Piece p) {
		unsigned int good = 0; // points in favor of p
		unsigned int bad = 0; // points against p
		unsigned int empty = 0; // neutral spots
		for (unsigned int i = 0; i < v.size(); i++) { // just enumerate how many of each
			good += (v[i] == p) ? 1 : 0;
			bad += (v[i] == otherPiece(p) || v[i] == p) ? 1 : 0;
			empty += (v[i] == Piece::Empty) ? 1 : 0;
		}
		// bad was calculated as (bad + good), so remove good
		bad -= good;
		return heurFunction(good, bad, empty);
	}

	/**
	 * my """heuristic function""" is pretty bad, but it seems to work
	 * it scores 2s in a row and 3s in a row
	 * param g - good points
	 * param b - bad points
	 * param z - empty spots
	 * return - the score as tabulated
	 */
	int heurFunction(unsigned int g, unsigned int b, unsigned int z) {
		int score = 0;
		if (g == 4) { score += 500001; } // preference to go for winning move vs. block
		else if (g == 3 && z == 1) { score += 5000; }
		else if (g == 2 && z == 2) { score += 500; }
		else if (b == 2 && z == 2) { score -= 501; } // preference to block
		else if (b == 3 && z == 1) { score -= 5001; } // preference to block
		else if (b == 4) { score -= 500000; }
		return score;
	}
}