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

void printInstructions() {
	cout << "Instructions --- (w): Up (s) = Down (a) = Left (d) = Right (q) = Quit\n";
}

void drawFullBoard(vector<vector<int>> board) {
	drawBoard(board);
	printInstructions();
}

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

int getSize(int i) {
	int size = 0;

	while (i > 0) {
		i /= 10;
		++size;
	}

	return size;
}

