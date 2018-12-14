#ifndef MSGAME_HPP_
#define MSGAME_HPP_
#include "MsCell.hpp"
#include <vector>
#include <ctime>

class MsGame {
	
	public:
		//constructor
		MsGame(int boardSizeX, int boardSizeY, int numberOfBombs, const char* fileName, time_t start_time);
		
		//public methods
		int step();
		
	private:
		//Private Methods
		void flood(int i, int j);
		void findBombNeighbors();
		void initializeBoard();
		void printBoard();
		void revealBoard();
		void countNeighbors(int i, int j);
		void updateLeaderFile(time_t end_time);

		//Private Variables
		std::vector<std::vector<MsCell> > board; 
		int sizeX, sizeY, bombs;
		const char* fileName;
		time_t start_time;
};

#endif /* MSGAME_HPP_ */