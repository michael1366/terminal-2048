#include "game.h"
#include <iostream>
#include <random>

using namespace std;

Game::Game(){
	board = vector<vector<int>>(4, vector<int>(4, 0));
	moves = vector<bool>(4);
	gameOver = false;
	gameWon = false;
	score = 0;

	cout << "     Welcome to 2048\n";

	endLess = getGameMode();

	placeTile();
	placeTile();
	drawFullBoard(board, score);
	updateMoves();
}

Game::Game(vector<vector<int>> testBoard){
	board = testBoard;
	moves = vector<bool>(4);
	gameWon = false;
	gameOver = false;
	score = 0;

	cout << "     Welcome to 2048\n";

	endLess = getGameMode();

	drawFullBoard(board, score);
	updateMoves();
}

bool Game::getGameMode() {
	while (true) {
		int choice;
		cout << "Choose a game mode:\n(1) Classic\n(2) Endless\n";

		if (cin >> choice) {
			if (choice == 1 || choice == 2) {
				clearScreen();
				return choice == 2;
				break;
			}
			else {
				clearScreen();
				cout << "Invalid choice. Please enter 1 or 2.\n";
			}
		}
		else {
			clearScreen();
			cout << "Invalid input. Please enter a number.\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}

	}
}

void Game::placeTile(){
	vector<vector<int>> list;

	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[0].size(); ++j) {
			if (board[i][j] == 0) list.push_back({ i, j });
		}
	}

	srand(time(0));
	vector<int> index = list.at(rand() % list.size());

	if (rand() % 10 == 0) {
		board[index[0]][index[1]] = 4;
	} else {
		board[index[0]][index[1]] = 2;
	}
}

void Game::updateMoves() {
	moves[UP] = canUp();
	moves[DOWN] = canDown();
	moves[LEFT] = canLeft();
	moves[RIGHT] = canRight();

	if (!moves[UP] && !moves[DOWN] && !moves[LEFT] && !moves[RIGHT]) gameOver = true;
}

bool Game::canUp() {
	for (int i = 0; i < board[0].size(); ++i) {
		int lastNum = 0;
		for (int j = board.size() - 1; j >= 0; --j) {
			if (lastNum != 0 && (board[j][i] == 0 || board[j][i] == lastNum)) return true;
			lastNum = board[j][i];
		}
	}

	return false;
}

bool Game::canDown() {
	for (int i = 0; i < board[0].size(); ++i) {
		int lastNum = 0;
		for (int j = 0; j < board.size(); ++j) {
			if (lastNum != 0 && (board[j][i] == 0 || board[j][i] == lastNum)) return true;
			lastNum = board[j][i];
		}
	}

	return false;
}

bool Game::canLeft() {
	for (int i = 0; i < board.size(); ++i) {
		int lastNum = 0;
		for (int j = board[0].size() - 1; j >= 0; --j) {
			if (lastNum != 0 && (board[i][j] == 0 || board[i][j] == lastNum)) return true;
			lastNum = board[i][j];
		}
	}

	return false;
}

bool Game::canRight() {
	for(int i = 0; i < board.size(); ++i) {
		int lastNum = 0;
		for (int j = 0; j < board[0].size(); ++j) {
			if (lastNum != 0 && (board[i][j] == 0 || board[i][j] == lastNum)) return true;
			lastNum = board[i][j];
		}
	}

	return false;
}

void Game::getMove() {
	string moveCheck;
	char move;

	while (true) {
		cout << "Enter your move: ";
		cin >> moveCheck;

		if (moveCheck.size() != 1) {
			clearScreen();
			drawFullBoard(board, score);
			cout << "Invalid move. Please try again. \n";
			continue;
		}
		else {
			move = moveCheck[0];
		}

		if (cin.fail() || (move != 'w' && move != 'a' && move != 's' && move != 'd')) {
			if (move == 'q') {
				gameOver = true;
				return;
			}

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			clearScreen();
			drawFullBoard(board, score);
			cout << "Invalid move. Please try again. \n";
			continue;
		}
		
		int index = -1;
		switch (move) {
			case 'w': index = 0; break;
			case 's': index = 1; break;
			case 'a': index = 2; break;
			case 'd': index = 3; break;
		}

		if (!moves[index]) {
			clearScreen();

			drawFullBoard(board, score);
			cout << "Move not possible. Try again. \n";
			continue;
		}
		
		executeMove(index);

		if (gameWon) gameOver = true;
		break;
	}

	if (gameOver) return;
	clearScreen();
	placeTile();
	drawFullBoard(board, score);
	updateMoves();
}

void Game::executeMove(int move) {
	switch (move) {
		case 0: moveUp(); break;
		case 1: moveDown(); break;
		case 2: moveLeft(); break;
		case 3: moveRight(); break;
	}
}

void Game::moveUp() {
	for (int i = 0; i < board[0].size(); ++i) {
		vector<int> vals;
		for (int j = 0; j < board.size(); ++j) {
			if (board[j][i] != 0) vals.push_back(board[j][i]);
		}

		getMerged(vals);

		for (int j = 0; j < board.size(); ++j) {
			board[j][i] = j >= vals.size() ? 0 : vals[j];
		}
	}
}

void Game::moveDown() {
	for (int i = 0; i < board[0].size(); ++i) {
		vector<int> vals;
		for (int j = board.size() - 1; j >= 0; --j) {
			if (board[j][i] != 0) vals.push_back(board[j][i]);
		}

		getMerged(vals);

		for (int j = 0; j < board.size(); ++j) {
			board[board.size() - 1 - j][i] = j >= vals.size() ? 0 : vals[j];
		}
	}
}

void Game::moveLeft() {
	for (int i = 0; i < board.size(); ++i) {
		vector<int> vals;
		for (int j = 0; j < board[0].size(); ++j) {
			if (board[i][j] != 0) vals.push_back(board[i][j]);
		}

		getMerged(vals);

		for (int j = 0; j < board[0].size(); ++j) {
			board[i][j] = j >= vals.size() ? 0 : vals[j];
		}
	}
}

void Game::moveRight() {
	for (int i = 0; i < board.size(); ++i) {
		vector<int> vals;
		for (int j = board[0].size() - 1; j >= 0; --j) {
			if (board[i][j] != 0) vals.push_back(board[i][j]);
		}

		getMerged(vals);

		for (int j = 0; j < board[0].size(); ++j) {
			board[i][board[0].size() - 1 - j] = j >= vals.size() ? 0 : vals[j];
		}
	}
}

void Game::getMerged(vector<int>& vec) {
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i] == vec[i - 1]) {
			vec[i - 1] += vec[i];

			score += vec[i - 1];
			if (!endLess && vec[i - 1] == 2048) gameWon = true;

			vec.erase(vec.begin() + i);
			i = 1;
		}
	}
}

bool Game::gameIsOver() {
	return gameOver;
}

void Game::endScreen() {
	clearScreen();
	drawTitle();
	drawBoard(board);

	if (!gameWon) {
		cout << "Game Over!\n" << "Final score: " << score;
	}
	else {
		cout << "You win!\n" << "Final score: " << score;
	}
	cout << "\nPress any key to exit";
	cin.get();
}