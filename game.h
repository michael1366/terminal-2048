#pragma once
#include "display.h"
#include <vector>

using namespace std;

class Game {
private:
	vector<vector<int>> board;
	vector<bool> moves;
	enum directions { UP, DOWN, LEFT, RIGHT };
	bool gameOver;
	int score;

public:
	Game();
	Game(vector<vector<int>> testGame);

	void placeTile();
	bool canUp();
	void updateMoves();
	bool canDown();
	bool canLeft();
	bool canRight();

	void getMove();
	void executeMove(int move);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void getMerged(vector<int>& vec);

	bool gameIsOver();
	void endScreen();
};