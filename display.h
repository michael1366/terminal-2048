#pragma once
#include <vector>

void drawLine();
void drawContent(std::vector<int> vec);
void drawBoard(std::vector<std::vector<int>> board);
void printInstructions();
void drawFullBoard(std::vector<std::vector<int>> board, int score);
void drawHeader(int score);
void drawTitle();
void drawScore(int score);
void clearScreen();


int getSize(int i);