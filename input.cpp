#include "input.h"
namespace c_4 {
	int getDifficulty(std::istream& in){
		int answer;
		in >> answer;
		return answer;
	}
	Turn getTurn(std::istream& in){
		Turn answer;
		std::string response;
		in >> response;
		if (response == "2") {
			answer = Turn::AI;
		}
		else {
			answer = Turn::Player;
		}
		return answer;
	}
	bool isContinuing(std::istream& in){
		bool answer = true;
		std::string response;
		in >> response;
		if (response == "no" || response == "No" || response == "NO" || response == "n" || response == "N") {
			answer = false;
		}
		return answer;
	}
}