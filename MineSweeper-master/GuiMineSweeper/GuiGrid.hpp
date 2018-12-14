#ifndef GUIGRID_HPP_
#define GUIGRID_HPP_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MsCell.hpp"
#include "MsGame.hpp"

class GuiGrid {

public:
	//constructor
	GuiGrid(int rows, int cols, int numOfBombs);

	//updates changes made to grid after a tile is clicked
	int Clicked(sf::Event e);
	void flood(int i, int j);
	void revealBoard();
	void resetGrid();
	bool hasWon();
//	int countMine();
	bool flagOnBomb(sf::Event e);
	char convertToString(int m);
	int writeLeader(std::string TimeData);
	int main();
	
	//getters
	std::vector<std::vector<int> > getGrid();
	sf::Sprite getTiles();
	sf::Sprite getSmilies();
	std::pair<int, int> getSmileNums();
	int getSquareSize();
	int getSmileSizeX();
	int getSmileSizeY();

	//setters
	void setSquareSize(int s);
	void setSmileSizes(int x, int y);
	void setSmileNums(int x, int y);
	bool hasLost;
	
	int score_B;
	
private:
	//sSize has pixel size of textures
	int rows, cols, sSize, smSizeX, smSizeY, numOfBombs;

	//contains pixel dimensions for each smiley face
	std::pair<int, int> smNums;

	//generated grid w/ numbers and bombs etc.
	std::vector<std::vector<MsCell> > grid;

	//plain tile grid - modify to reveal corresponding tiles in grid
	std::vector<std::vector<int> > coverGrid;

	//std::vector<std::pair<std::string, float>> score_B;

	sf::Sprite tiles, smilies;
	sf::Texture tile, smiley;
	MsGame game;
};

#endif /* GUIGRID_HPP_ */
