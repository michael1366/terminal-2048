#include "display.h"
#include <iostream>

using namespace std;

void drawLine() {
	cout << "+-----+-----+-----+-----+\n";
}

void drawContent(vector<int> vec) {
	for (int i : vec) {
		if (i == 0) {
			cout << "|     ";
		}
		else {
			int size = getSize(i);
			cout << "|";

			for (int j = 0; j < (5 - size) / 2; ++j) {
				cout << " ";
			}

			cout << i;

			for (int j = 0; j < (6 - size) / 2; ++j) {
				cout << " ";
			}
		}
	}

	cout << "|\n";
}

void drawBoard(vector<vector<int>> board) {
	for (vector<int> vec : board) {
		drawLine();
		drawContent(vec);
	}
	drawLine();
}

void drawHeader(int score) {
	drawTitle();
	drawScore(score);
}

void drawTitle() {
	cout << string(8, ' ') << "2048 Game\n";
}

void drawScore(int score) {
	int size = getSize(score);
	cout << string((19 - size) / 2, ' ') << "Score: " << score << string((18 - size) / 2, ' ') << "\n";
}

void printInstructions() {
	cout << "Instructions --- (w): Up (s) = Down (a) = Left (d) = Right (q) = Quit\n";
}

void drawFullBoard(vector<vector<int>> board, int score) {
	drawHeader(score);
	drawBoard(board);
	printInstructions();
}

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

int getSize(int i) {
	if (i == 0) return 1;
	int size = 0;

	while (i > 0) {
		i /= 10;
		++size;
	}

	return size;
}

