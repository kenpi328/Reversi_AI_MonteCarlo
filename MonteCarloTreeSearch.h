#pragma once
#include "Othello.h"
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

std::pair<int, int> monteCarloSearch (int **currentBoard);
int evaluate(int** currentBoard);
int** copyBoard(int **toBoard, int** fromBoard  );

