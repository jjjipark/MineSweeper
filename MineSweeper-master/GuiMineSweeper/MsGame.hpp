#ifndef MSGAME_HPP_
#define MSGAME_HPP_
#include "MsCell.hpp"
#include <vector>

class MsGame {
	public:
		MsGame(int boardSizeX, int boardSizeY, int numberOfBombs);
		~MsGame();
		
		void initializeBoard();

		std::vector<std::vector<MsCell> > getBoard();

	private:
		// Private methods
		void findBombNeighbors();
		void countNeighbors(int i, int j);

		std::vector<std::vector<MsCell> > board; 
		int sizeX, sizeY;
		int bombs;
};

#endif /* MSGAME_HPP_ */
