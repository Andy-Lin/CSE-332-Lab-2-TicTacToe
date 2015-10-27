#include "Board.h"
#define QUIT 1
#define DRAW 2

//This is a test
// constructor initializes the board and the draw status
Board::Board(bool playStatus) {
	numMoves = 0;
	xCoor = 999;
	yCoor = 999;
	player = "X";
	autoPlay = playStatus;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			board[i][j] = " ";
		}
	}
	board[0][0] = "4";
	board[1][0] = "3";
	board[2][0] = "2";
	board[3][0] = "1";
	board[4][0] = "0";
	board[5][1] = "0";
	board[5][2] = "1";
	board[5][3] = "2";
	board[5][4] = "3";
	board[5][5] = "4";
}

// overload the ostream operator to print out the current state of the board.
// This works fine in the main statement but I couldn't figure out how to call
// it in the turn and play methods
std::ostream& operator <<(std::ostream& out, const Board::Board& bd) {

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			out << bd.board[i][j] << " ";
		}
		out << " " << std::endl;
	}

	return out;
}

// method to check whether a 3 in a row has happened
// if it has, this method returns true
bool Board::done() {

	// check whether any of the rows are three in a row
	for (int row = 1; row < 4; ++row) {
		if (board[row][2] == " ") {
			continue;
		} else if (board[row][2] == board[row][3]
				&& board[row][3] == board[row][4]) {
			return true;
		}
	}

	// check whether any of the columns are three in a row
	for (int col = 2; col < 5; ++col) {
		if (board[1][col] == " ") {
			continue;
		} else if (board[1][col] == board[2][col]
				&& board[2][col] == board[3][col]) {
			return true;

		}
	}

	// check whether the diagonals are three in a row
	if (board[2][3] == " ") {
		return false;

	} else if (board[1][2] == board[2][3] && board[2][3] == board[3][4]) {
		return true;

	} else if (board[3][2] == board[2][3] && board[2][3] == board[1][4]) {
		return true;
	}

	return false;
}

// method to check whether there is any more moves left or whether
// the game is done. If either of those are true, this method returns true
bool Board::draw() {
	++numMoves;

	// checks to see whether all 9 moves have been made and whether the
	// game is done
	if (numMoves == 9 || this->done()) {
		return true;
	}

	return false;
}

// method to prompt the user for an input and pass that input into
// references to xCoor and yCoor
int Board::prompt(unsigned int& x, unsigned int& y) {
	std::string input;

	while (1) {

		unsigned int tempX = 99;
		unsigned int tempY = 99;

		// prompts and read in user input
		std::cout << "Enter coordinates of next move or quit to quit"
				<< std::endl;
		getline(std::cin, input);
		std::cout << std::endl;

		// get rid of white spaces
		std::istringstream iss(input);
		std::string result;
		while (iss) {
			std::string sub;
			iss >> sub;
			result += sub;
		}

		// checks to see whether the user typed quit
		if (result == "quit") {
			return QUIT;
		}

		std::stringstream ss;

		//checks to see the format of what is entered
		std::string commaCheck;
		std::string endingCheck;

		//get first index of results (",") and the third index of
		//the result (" "). If the index does not exist, it will
		// give those a value of " ".
		ss << result[1] << " ";
		ss >> commaCheck;
		size_t len = result.size();

		// checks to see whether the input is exactly 3 indexes long
		// and that the second index is a comma
		if (commaCheck == "," && len == 3) {
			std::stringstream ss;
			ss << result[0] << " " << result[2];
			ss >> tempX >> tempY;
		} else {
			std::cout << "You have entered a invalid command" << std::endl;
			continue;
		}

		// checks to see if the coordinates are within the range
		// if they are, exit the loop
		if (1 <= tempX && tempX <= 3 && 1 <= tempY && tempY <= 3) {
			x = tempX;
			y = tempY;
			return 0;
		} else {
			std::cout << "Coordinates not valid" << std::endl;
		}
	};
}

// method to determine the players turn and to play the players
// marker on the position he/she specifies if it is valid
int Board::turn() {


	// if the player wants auto play, only this portion of the code runs
	if (autoPlay && player == "O") {
		auto_player();
		player = "X";
		return 0;
	}

	std::cout << std::endl;
	std::cout << "Player " << player << "'s turn" << std::endl;

	unsigned int& x = xCoor;
	unsigned int& y = yCoor;
	unsigned int tempX;
	unsigned int tempY;

	while (1) {

		// if the player decides to quit return failure code stating the
		// player has quit
		if (prompt(x, y) == QUIT) {
			return QUIT;
		}

		// convert the input values into coordinate values
		switch (x) {
		case 3:
			tempX = 1;
			break;
		case 1:
			tempX = 3;
			break;
		default:
			tempX = x;
			break;
		}
		tempY = y + 1;

		// set board position to the player's marker if the position is empty
		if (board[tempX][tempY] == " ") {
			board[tempX][tempY] = player;
			break;
		} else {
			std::cout << "Coordinates have already been played" << std::endl;
		}
	}

	// output the board. Could not figure out how to output the board using
	// the overloaded << operator with the class.
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			std::cout << board[i][j] << " ";
		}
		std::cout << " " << std::endl;
	}

	// prints out the moves the player has made
	std::stringstream ss;
	ss << x << "," << y << "; ";
	if (player == "X") {
		xMoves += ss.str();
		std::cout << "Player " << player << ": " << xMoves << std::endl
				<< std::endl;
	} else if (player == "O") {
		yMoves += ss.str();
		std::cout << "Player " << player << ": " << yMoves << std::endl
				<< std::endl;
	}

	//Alternates the player's turn
	if (player == "X") {
		player = "O";
	} else {
		player = "X";
	}

	return 0;

}

// plays the game by looping through turn() follow by done() and
// lastly draw until the game is done
int Board::play() {

	//output the board for the board
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			std::cout << board[i][j] << " ";
		}
		std::cout << " " << std::endl;
	}

	// loops continuous until the one of the condition is met
	while (1) {
		// returns error code of QUIT (1) when the player decides to quit
		if (this->turn() == QUIT) {
			std::cout << numMoves << " turn(s) have been made." << std::endl;
			std::cout << "Player " << player << " has decided to quit"
					<< std::endl;
			return QUIT;
		}

		// returns a success (0) if a player wins
		if (this->done()) {
			if (player == "X") {
				std::cout << "Player O has won!" << std::endl;
				return 0;
			} else {
				std::cout << "Player X has won!" << std::endl;
				return 0;
			}
		}

		// returns error code of DRAW (2) when the game ends with no winner
		if (this->draw()) {
			std::cout << numMoves << " turns have been made but no winner"
					<< std::endl;
			return DRAW;
		}
	}
}

// creates an automatic player
void Board::auto_player() {

	// first check to see if O can win. If it cannot, check to block
	// if all else fails, do a random move.
	if (check_win()) {
		std::cout << "Computer moving to win!" << std::endl;
	} else if (block_win()) {
		std::cout << "Computer moving to block!" << std::endl;
	} else {
		random_move();
		std::cout << "Computer making random move!" << std::endl;
	}

	//print out the board
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			std::cout << board[i][j] << " ";
		}
		std::cout << " " << std::endl;
	}
}

// method to find a random move when the computer does not
// need to block or cannot win in the next turn.
void Board::random_move() {

	while (1) {
		// use random number generator to put O into an open
		// position.
		srand(time(0));
		int randCol = 2 + (rand() % 3);
		int randRow = 1 + (rand() % 3);
		if (board[randRow][randCol] == " ") {
			board[randRow][randCol] = "O";
			break;
		}
	}
}

// method to block the player from winning
bool Board::block_win() {

	// goes through the whole board to see if X can win
	// at that position, if X can, set that position to
	// O and return true;
	for (int i = 1; i < 4; ++i) {
		for (int j = 2; j < 5; ++j) {
			if (board[i][j] == " ") {
				board[i][j] = "X";
				if (this->done()) {
					board[i][j] = "O";
					return true;
				} else {
					board[i][j] = " ";
				}
			}
		}
	}
	return false;
}

// method for the computer to win
bool Board::check_win() {
	for (int i = 1; i < 4; ++i) {
		for (int j = 2; j < 5; ++j) {
			if (board[i][j] == " ") {
				board[i][j] = "O";
				if (this->done()) {
					board[i][j] = "O";
					return true;
				} else {
					board[i][j] = " ";
				}
			}
		}
	}
	return false;
}
