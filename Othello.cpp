#include "Othello.h"
// set (3,3) and (4,4) to white(1), and set (3,4) and (4,5)
int** newGame() 
{
	int** Board;
	Board = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		Board[i] = new int[8];
		for (int j = 0; j < 8; j++)
		{
			if ((i == 3 && j == 3) || (i == 4 && j == 4))
				Board[i][j] = 1;
			else if ((i == 3 && j == 4) || (i == 4 && j == 3))
				Board[i][j] = -1;
			else
				Board[i][j] = 0;
		}
	}
	return Board;
}
//modify location y x to whiteOrBlack
int** modifyBoard(int **b, int y, int x, int whiteOrBlack)
{
	
	//modify board
	int** Board;
	Board = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		Board[i] = new int[8];
		for (int j = 0; j < 8; j++)
		{
			if (i == y && j == x)
				Board[i][j] = whiteOrBlack;
			else
				Board[i][j] = b[i][j];

		}
	}
	freeBoard(b);
	return Board;
}

void freeBoard(int** b) {
	for (int i = 0; i < 8; i++){
		delete[] b[i];
	}
	delete[] b;
	b = 0;
}

int** flip(int **board, int y ,int x ,int whiteOrBlack) {
	if (NorthCheckAvailability(board, y, x, whiteOrBlack)) {
		int yaxis = y - 1;
		while (board[yaxis][x] == -1*whiteOrBlack) {
			board = modifyBoard(board, yaxis, x, whiteOrBlack);
			//flip(board, yaxis, x, whiteOrBlack);
			yaxis -= 1;
		}
	}
	if (EastCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x + 1;
		while (board[y][xaxis] == -1*whiteOrBlack) {
			board= modifyBoard(board, y, xaxis, whiteOrBlack);
			xaxis += 1;
		}
	}
	if (SouthCheckAvailability(board, y, x, whiteOrBlack)) {
		int yaxis = y + 1;
		while (board[yaxis][x] == -1 * whiteOrBlack) {
			board = modifyBoard(board, yaxis, x, whiteOrBlack);
			yaxis += 1;
		}
	}
	if (WestCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x - 1;
		while (board[y][xaxis] == -1 * whiteOrBlack) {
			board = modifyBoard(board, y, xaxis, whiteOrBlack);
			xaxis -= 1;
		}
	}
	if (SouthWestCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x - 1;
		int yaxis = y + 1;
		while (board[yaxis][xaxis] == -1 * whiteOrBlack) {
			board = modifyBoard(board, yaxis, xaxis, whiteOrBlack);
			xaxis -= 1;
			yaxis += 1;
		}
	}
	if (SouthEastCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x + 1;
		int yaxis = y + 1;
		while (board[yaxis][xaxis] == -1 * whiteOrBlack) {
			board = modifyBoard(board, yaxis, xaxis, whiteOrBlack);
			xaxis += 1;
			yaxis += 1;
		}
	}
	if (NorthWestCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x - 1;
		int yaxis = y - 1;
		while (board[yaxis][xaxis] == -1 * whiteOrBlack) {
			board = modifyBoard(board, yaxis, xaxis, whiteOrBlack);
			xaxis -= 1;
			yaxis -= 1;
		}
	}
		
	if (NorthEastCheckAvailability(board, y, x, whiteOrBlack)) {
		int xaxis = x + 1;
		int yaxis = y - 1;
		while (board[yaxis][xaxis] == -1 * whiteOrBlack) {
			board = modifyBoard(board, yaxis, xaxis, whiteOrBlack);
			xaxis += 1;
			yaxis -= 1;
		}
	}
	return board;
}
//return a vector of available moves (string or array)
std::vector<std::pair<int, int>> availableMove(int** board, int whiteOrBlack) 
{
	std::vector<std::pair<int, int>> moves;
	//for each 
	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {
			if (checkAvailability(board, i, j, whiteOrBlack) == true) {
				std::pair<int, int> availableLocation(i, j);
				moves.push_back(availableLocation);
			 }
			
		}
	}
	return moves;
}

bool checkAvailability(int** board, int y, int x, int whiteOrBlack) {
	 if (board[y][x] != 0) //if location y x is filled 
		 return false;
	 return (NorthCheckAvailability(board, y, x, whiteOrBlack) ||
		 EastCheckAvailability(board, y, x, whiteOrBlack) ||
		 SouthCheckAvailability(board, y, x, whiteOrBlack) ||
		 WestCheckAvailability(board, y, x, whiteOrBlack) ||
		 SouthWestCheckAvailability(board, y, x, whiteOrBlack) ||
		 SouthEastCheckAvailability(board, y, x, whiteOrBlack) ||
		 NorthWestCheckAvailability(board, y, x, whiteOrBlack) ||
		 NorthEastCheckAvailability(board, y, x, whiteOrBlack)
		 );
}
//check if location ( y, x ) is available when "whiteOrBlack"'s turn
bool NorthCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	//north 
	//check if the block above the empty block is oppnent
	//If it is opponent go north till the end of the board,
	// and if there is a "turn" between the search return true
	if (y >= 2) { //if the box above y x is "opponent"
		if (board[y - 1][x] == opponent){
			for (int yaxis = y - 2; yaxis >= 0; yaxis--) {
				if (board[yaxis][x] == turn) { //if the box above y x is empty or same as turn
					return true;
				}
			}
		}
	}
	return false;
	
}

bool EastCheckAvailability(int** board, int y, int x, int whiteOrBlack){
	//East
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if ( x < 6 ) {
		if(board[y][x + 1] == opponent){
			for (int xaxis = x + 2; xaxis < 8; xaxis++) {
				if (board[y][xaxis] == turn) { //if the box above y x is empty or same as turn
					return true;
				}
			}
		}
	}
	return false;

}
bool SouthCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	int turn = whiteOrBlack;
	int opponent = turn * -1;


	if (y < 6 ) { //if the box above y x is "opponent"
		if (board[y + 1][x] == opponent) {
			for (int yaxis = y + 2; yaxis < 8; yaxis++) {
				if (board[yaxis][x] == turn) { //if the box above y x is empty or same as turn
					return true;
				}
			}
		}
	}
	return false;

}
bool WestCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if (x >= 2) {
		if (board[y][x - 1] == opponent) {
			for (int xaxis = x - 2; xaxis >= 0; xaxis--) {
				if (board[y][xaxis] == turn) { //if the box above y x is empty or same as turn
					return true;
				}
			}
		}
	}
	return false;

}
bool SouthWestCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if (y < 6 && x >= 2 ) { //y >= 0 && x >= 2 && board[y + 1][x - 1] == opponent
		if (board[y + 1][x - 1] == opponent) {
			int yaxis = y + 2;
			int xaxis = x - 2;
			while (xaxis >= 0 && yaxis < 8) {
				if (board[yaxis][xaxis] == turn) {
					return true;
				}
				xaxis--;
				yaxis++;
			}
		}

	}
	return false;

}
bool SouthEastCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if (x < 6 && y < 6 ) {
		if (board[y + 1][x + 1] == opponent) {
			int xaxis = x + 2;
			int yaxis = y + 2;
			while (xaxis < 8 && yaxis < 8) {
				if (board[yaxis][xaxis] == turn) {
					return true;
				}
				xaxis++;
				yaxis++;
			}
		}
		
	}
	return false;
}
bool NorthWestCheckAvailability(int** board, int y, int x, int whiteOrBlack) {

	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if (x >= 2 && y >= 2 ) {
		if ( board[y - 1][x - 1] == opponent) {
			int xaxis = x - 2;
			int yaxis = y - 2;
			while (xaxis >= 0 && yaxis >= 0) {
				if (board[yaxis][xaxis] == turn) {
					return true;
				}
				xaxis--;
				yaxis--;
			}
		}

	}
	return false;

}
bool NorthEastCheckAvailability(int** board, int y, int x, int whiteOrBlack) {
	int turn = whiteOrBlack;
	int opponent = turn * -1;

	if (x < 6 && y >= 2 ) {
		if (board[y - 1][x + 1] == opponent) {
			int yaxis = y - 2;
			int xaxis = x + 2;
			while (yaxis >= 0 && xaxis < 8) {
				if (board[yaxis][xaxis] == turn) {
					return true;
				}
				xaxis++;
				yaxis--;
			}
		}

	}
	return false;
}

bool gameEnd(int** b) {
	std::vector<std::pair<int, int>>black = availableMove( b, -1);
	std::vector<std::pair<int, int>>white = availableMove(b, 1);
	if (black.size() == 0 && white.size() == 0) {
		int blackCounter = 0;
		int whiteCounter = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (b[i][j] == -1)
					blackCounter++;
				else if (b[i][j] == 1)
					whiteCounter++;
			}
		}
		std::string status = " ";
		if (blackCounter == whiteCounter)
			status = "Draw! ";
		else if (blackCounter > whiteCounter)
			status = "Black(Cross) Win!";
		else
			status = "White(Circle) Win!";

		std::cout << status << " #Black(Cross) = " << blackCounter << " #White(Circle) = " << whiteCounter << std::endl;
		return true;
	}
	return false;
}

//choose a move from available move vector by random
std::pair<int, int> randomMove(std::vector<std::pair<int, int>> moves)
{
	//0 to moves.size() - 1
	srand(time(NULL));
	int chosenIndex = (rand() % moves.size());
    std::pair<int, int> chosen(moves[chosenIndex].first, moves[chosenIndex].second);
	return chosen;
}
void printBoard(int **b) 
{
	char black = 'X';
	char white = 'O';
	std::cout << "  0  1  2  3  4  5  6  7" << std::endl;
	for (int i = 0; i < 8; i++) {
		std::cout << i << " ";
		for (int j = 0; j < 8; j++) {
			char symbol = ' ';
			if (b[i][j] == -1)
				symbol = black;
			else if (b[i][j] == 1)
				symbol = white;
			else
				symbol = '-';

			std::cout << symbol << "  ";

		}
		//std::cout << std::endl;
		std::cout << std::endl;
	}
}