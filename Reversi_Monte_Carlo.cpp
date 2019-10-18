// Reversi_Monte_Carlo.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "Othello.h"
#include "MonteCarloTreeSearch.h"
#include <string>
//#include "Reversi.h"
int main()
{
	std::cout << "Reversi Start!" << std::endl;
	std::cout << "You are X(black)" << std::endl;
	std::cout << "Comupter are O(white)" << std::endl;
	std::cout << "Let's start with your turn! " << std::endl;
	std::cout << "Input format is <y-axis, x-axis>" << std::endl;
	//Start the game with users turn
	int** board = newGame();
	printBoard(board);
	while (gameEnd(board) == false) {

		std::cout << "Available blocks are <y-axis, x-axis>: " << std::endl;;
		//show users available move and get their input
		std::vector<std::pair<int, int>> moves = availableMove(board, -1);
		for (int k = 0; k < moves.size(); k++) {
			std::cout << "< " << moves[k].first << ",   " << moves[k].second << ">" << std::endl;
		}
		int x, y;
		std::cout << "Choose a block from above" << std::endl;
		std::cout << "Your Input :" << std::endl;
		std::cout << "Enter y: ";
		std::cin >> y;
		std::cout << "Enter x: ";
		std::cin >> x;
		std::cout << "Your Input : " << "<" << y << ", " << x << ">" << std::endl;

		bool correctInput = false;
		for (int k = 0; k < moves.size(); k++) {
			if (moves[k].first == y && moves[k].second == x)
				correctInput = true;
		}
		if (!correctInput) {
			std::cout << "Wrong Input! Please play again!" << std::endl;
			return 0;
		}

		//Enter the input and flip
		if (moves.size() > 0) {
			board = modifyBoard(board, y, x, -1);
			board = flip(board, y, x, -1);
		}
		else {
			std::cout << "No box available!" << std::endl;
		}
		printBoard(board);


		std::vector<std::pair<int, int>> Cmoves = availableMove(board, 1);
		std::cout << "Computer's turn!" << std::endl;
		if (Cmoves.size() > 0) {
			//std::pair<int, int> chosen = randomMove(Cmoves);
			std::pair<int, int> chosen = monteCarloSearch(board);
			board = modifyBoard(board, chosen.first, chosen.second, 1);
			board = flip(board, chosen.first, chosen.second, 1);
		}
		else {
			std::cout << "No box available!" << std::endl;
		}
		printBoard(board);
	}

	/*
	//TEST
	board = modifyBoard(board, 5, 4, -1);
	board = modifyBoard(board, 4, 4, -1);
	std::cout << NorthWestCheckAvailability(board, 0, 0, -1) << std::endl;
	std::cout << NorthWestCheckAvailability(board, 4, 5, 1) << std::endl;
	std::vector<std::pair<int, int>> moves = availableMove(board, 1);
	std::cout << moves.size() << std::endl;
	
	for (int k = 0; k < moves.size(); k++) {
		std::cout << "Options:" << std::endl;
		std::cout <<"y is " << moves[k].first <<"  x is " << moves[k].second << std::endl;
	}
	std::pair<int, int> chosen = randomMove(moves);
	std::cout << "Chose y is " << chosen.first << "  x is " << chosen.second << std::endl;
	
	printBoard(board);
	*/


	return 0;
	
}
