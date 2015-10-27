//============================================================================
// Name        : TicTacToe.cpp
// Author      : Andy Lin
// Description : A tic tac toe game
//============================================================================

#include <iostream>
#include "Board.h"
#include <sstream>



int main(int argc, char* argv[]) {

	if(argc == 2 && argv[1]==std::string("TicTacToe")){
		Board board1(false);
		return board1.play();
	} else if (argc == 3 && argv[1]==std::string("TicTacToe") && argv[2]==std::string("auto_player")){
		std::cout << "You have decide to play against a computer" << std::endl;
		Board board2(true);
		return board2.play();
	} else {
		std::cout << "Wrong usage" << std::endl;
		std::cout << "Correct usage is program_name TicTacToe" << std::endl;
		std::cout << "or specify auto_player at end of usage to play against computer" << std::endl;
	}


	return 0;
}
