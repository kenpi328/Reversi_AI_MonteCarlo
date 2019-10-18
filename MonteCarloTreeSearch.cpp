#include "MonteCarloTreeSearch.h"

std::pair<int, int> monteCarloSearch(int** currentBoard) {

	
	std::vector<std::pair<int, int>> Imoves = availableMove(currentBoard, 1); //computer so must be white
	int ArrSize = Imoves.size();
	int* values = new int[ArrSize];
	for (int i = 0; i < ArrSize; i++) {

		for (int j = 0; j < 30; j++) {
			int** board = newGame();
			copyBoard(board, currentBoard);
			board = modifyBoard(board, Imoves[i].first, Imoves[i].second, 1);
			while (gameEnd(board) == false) {

				

				std::vector<std::pair<int, int>> bMoves = availableMove(board, -1); //computer black
				if (bMoves.size() > 0) {
					std::pair<int, int> chosen = randomMove(bMoves);
					board = modifyBoard(board, chosen.first, chosen.second, -1);
					board = flip(board, chosen.first, chosen.second, -1);
				}

				std::vector<std::pair<int, int>> wMoves = availableMove(board, 1); //computer so must be white

				if (wMoves.size() > 0) {
					std::pair<int, int> chosen = randomMove(wMoves);
					board = modifyBoard(board, chosen.first, chosen.second, 1);
					board = flip(board, chosen.first, chosen.second, 1);
				}
			}
			freeBoard(board);


		

			int eval = evaluate(board); //return difference of white and black piece
			if (eval == 0) //draw
				values[i] += 0;
			else if (eval < 0)//lose
				values[i] = -1;
			else if (eval > 0 && eval < 5)//win
				values[i] += 1;
			else  //Computer Wins with more than 5 difference
				values[i] += 2;


		}
	
		
	}
	int largestVal = values[0];
	int largestidx = 0;
	for (int k = 1; k < ArrSize; k++) {
		if (largestVal < values[k]) {
			largestVal = values[k];
			largestidx = k;
		}

	}
	std::pair<int, int> choose(Imoves[largestidx].first, Imoves[largestidx].second);
	return choose;
	
	
}
int evaluate(int** currentBoard) {
	int blackCounter = 0;
	int whiteCounter = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (currentBoard[i][j] == -1)
				blackCounter++;
			else if (currentBoard[i][j] == 1)
				whiteCounter++;
		}
	}

	int eval = whiteCounter - blackCounter;
	return eval;
}

int** copyBoard(int** toBoard, int** fromBoard)
{

	//modify board
	
	toBoard = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		toBoard[i] = new int[8];
		for (int j = 0; j < 8; j++)
		{
	
				toBoard[i][j] = fromBoard[i][j];

		}
	}
	//freeBoard(toBoard);
	return toBoard;
}
