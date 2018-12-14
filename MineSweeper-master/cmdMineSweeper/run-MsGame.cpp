#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "MsGame.hpp"

using namespace std;

int main( int argc, const char* argv[] ) {
	
	int boardX=0, boardY=0, bombs=0;
	string level;
	const char* fileName = "@@No File@@";
	
	//checks for the leader board file and opens if found
	if( argc != 2 ) {
        std::cout << "\nNo leader board file added. \nFeel free to play with limited functionality\n" << std::endl;
    } else {
		fileName = argv[1];
	}
	
	//initialize variables from user input
	std::cout << "Please enter the level of difficulty (b (Beginner), i (Intermediate), e (Expert), c (Custom)): ";
	
	std::cin >> level;

	while ((level != "b") & (level != "i") & (level != "e") & (level != "c")){
		std::cout << "\nIncorrect input.\nPlease enter the level of difficulty (b (Beginner), i (Intermediate), e (Expert), c (Custom)): ";
		std::cin.clear();
		cin.ignore(256,'\n');
		std::cin >> level;
		std::cout << "\n";
	}
	
	if (level == "b") {
		boardX = 8;
		boardY = 8;
		bombs = 1;
	} else if (level == "i") {
		boardX = 16;
		boardY = 16;
		bombs = 40;
	} else if (level == "e") {
		boardX = 16;
		boardY = 31;
		bombs = 99;
	} else if (level == "c") {
		
		std::cout << "Please enter the size of the grid (height width) [2, 50]: ";		
		std::cin >> boardX >> boardY;
		
		while ((boardX <= 1) || (boardX > 50) || (boardY <= 1) || (boardY > 50) || cin.fail()){
			std::cout << "\nIncorrect input.\nPlease enter the size of the grid (height width): ";
			std::cin.clear();
			cin.ignore(256,'\n');
			std::cin >> boardX >> boardY;
			std::cout << "\n";
		}

		std::cout << "Please enter the number of bombs [1, " << boardY*boardX << "]:";
		std::cin >> bombs;

		while((bombs > boardY*boardX) || cin.fail() || bombs <= 0 ) {
			std::cout << "\nIncorrect input.\nPlease enter the number of bombs: ";
			std::cin.clear();
			cin.ignore(256,'\n');
			std::cin >> bombs;
			std::cout << "\n";
		}
	}

	std::cout << std::endl;
		
	std::srand(std::time(NULL));

	time_t start_time = std::time(NULL);
	MsGame game(boardX, boardY, bombs, fileName, start_time);
	
	//step through game
	while(game.step() == 1){
		continue;
	}
	
	return 0;
}
