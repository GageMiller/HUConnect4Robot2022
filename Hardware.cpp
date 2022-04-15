#include "Hardware.h"
#include <iostream> // exclude if implementing hardware
namespace c_4 {
	void positionDropper(int col){
		int motorOn = 15 + col * 20; // arbitrary place holders
		int motorPin = 1;
		//wait motorOn
		motorPin = 0;
		std::cout << "Motor ran for " << motorOn << " seconds"; // exclude if implementing hardware
	}
	void returnDropper(){
		bool limiter = false;
		int motorPin = 1;
		int i = 0;
		while (!limiter) {
			if (i > 1000) {
				limiter = true;
			}
		}
		motorPin = 0;
	}
	void dropPiece(){
		//servo go to drop angle
		//servo return to original angle
	}
}