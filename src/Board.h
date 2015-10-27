#ifndef BOARD_H_
#define BOARD_H_

#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Board{

	bool autoPlay;

	std::string board[6][6];

	// a variable to keep track of how many moves have been made
	unsigned int numMoves;

	// variables to keep track of the x and y coordinates
	unsigned int xCoor;
	unsigned int yCoor;

	// variable to keep track of whose turn it is
	std::string player;

	// variables to keep track of the moves that have been made
	std::string xMoves;
	std::string yMoves;


public:
	Board(bool playStatus);
	bool done();
	bool draw();
	int prompt(unsigned int& x, unsigned int& y);
	int turn();
	int play();
	void auto_player();
	bool block_win();
	bool check_win();
	void random_move();

	friend std::ostream& operator << (std::ostream& out, const Board& bd);
};




#endif /* BOARD_H_ */
