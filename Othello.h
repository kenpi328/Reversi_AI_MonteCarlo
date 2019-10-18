#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//save state. Empty = 0, white = 1, black = -1
int** newGame(); // set (3,3) and (4,4) to white(1), and set (3,4) and (4,3)
int** modifyBoard(int** b, int y, int x, int whiteOrBlack);
void freeBoard(int** b);
int** flip(int** board, int y, int x, int whiteOrBlack);
std::vector<std::pair<int, int>> availableMove(int** board, int whiteOrBlack); //return available move to an vector
bool checkAvailability(int** board, int y, int x, int whiteOrBlack);//check if location ( y, x ) is available for whiteOrBlack

bool NorthCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool EastCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool SouthCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool WestCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool SouthWestCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool SouthEastCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool NorthWestCheckAvailability(int** board, int y, int x, int whiteOrBlack);
bool NorthEastCheckAvailability(int** board, int y, int x, int whiteOrBlack);

bool gameEnd(int**b);
std::pair<int,int> randomMove(std::vector<std::pair<int, int>> moves); //choose a move from available move by random
void printBoard(int **b);