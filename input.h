#pragma once
#include "board.h"
#include <iostream>

namespace c_4 {
	int getDifficulty(std::istream& in);
	Turn getTurn(std::istream& in);
	bool isContinuing(std::istream& in);
}
