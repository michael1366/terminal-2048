#include <iostream>
#include "game.h"


int main(){
	vector<vector<int>> testBoard = {
		{0, 2, 0, 0},   // row 0 
		{0, 2, 0, 0},   // row 1
		{0, 0, 0, 0},   // row 2
		{0, 0, 0, 0}    // row 3 
	};

	Game game;
	while (!game.gameIsOver()) {
		game.getMove();
	}
	game.endScreen();
}