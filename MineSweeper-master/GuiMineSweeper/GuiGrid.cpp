#include <time.h>
#include "GuiGrid.hpp"
#include "SFML/Audio.hpp"
#include <sstream>
#include <iostream>
#include <fstream>


using namespace sf;

GuiGrid::GuiGrid(int rows, int cols, int numOfBombs) : game(MsGame(rows, cols, numOfBombs)) {
	this->rows = rows;
	this->cols = cols;
	this->numOfBombs = numOfBombs;
	this->coverGrid = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 10));

	std::vector<std::vector<MsCell>> g = game.getBoard();
	this->grid = g;

	tile.loadFromFile("tiles.jpg");
	smiley.loadFromFile("110454.jpg");

	this->tiles = Sprite(tile);
	this->smilies = Sprite(smiley);
	this->sSize = 32;
	this->smNums = std::make_pair(0, 0);
	this->smSizeX = 146/2;
	this->smSizeY = 147/2;

	this->hasLost = false;
}

void GuiGrid::flood(int i, int j) {
	//if top grid is a plain tile and has no nearby bombs...
	if(this->coverGrid[i][j] == 10 && this->grid[i][j].getBombNeighbors() == 0) {
		this->coverGrid[i][j] = grid[i][j].id;
		for(int a = -1; a < 2; a++) {
			for(int b = -1; b < 2; b++) {
				if((i+a > -1 && j+b > -1) && (i+a < rows && j+b < cols)) {
					this->flood(i+a, j+b);
				}
			}
		}
	}
	if(grid[i][j].getBombNeighbors() != 0) {
		this->coverGrid[i][j] = grid[i][j].id;
	}
	return;
}

int GuiGrid::Clicked(Event e) {
	//update smiley values to later choose correct part of smiley texture
	smNums.first = 0;
	smNums.second = 0;
	
	//get x and y pixel coordinates for each tile
	int x = e.mouseButton.x / sSize;
	int y = (e.mouseButton.y - smSizeY) / sSize;

	//left click uncovers corresponding tile(s) in the generated grid
	if(e.mouseButton.button == Mouse::Left) {
		if(grid[x][y].getBombNeighbors() != 0) {
			coverGrid[x][y] = grid[x][y].id;
		} else {
			flood(x, y);
		}
		return coverGrid[x][y];
	//displays flag on appropriate tile
	} else if(e.mouseButton.button == Mouse::Right && coverGrid[x][y] == 10) {
		coverGrid[x][y] = 11;
		return coverGrid[x][y];
	//remove flag
	} else if(e.mouseButton.button == Mouse::Right && coverGrid[x][y] == 11) {
		coverGrid[x][y] = 10;
		return coverGrid[x][y];

	}
	return -1;
}


bool GuiGrid::flagOnBomb(Event e){

	int x = e.mouseButton.x / sSize;
	int y = (e.mouseButton.y - smSizeY) / sSize;
	
	if ( e.mouseButton.button == Mouse::Right && coverGrid[x][y] == 10 && grid[x][y].id == 9){
		return true;
	}
	return false;
}

		
void GuiGrid::revealBoard() {
	//let the covering grid equal the grid w/ generated bombs/values
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			coverGrid[i][j] = grid[i][j].id;
		}
	}
}

bool GuiGrid::hasWon() {
	int count = 0;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			//check if user has successfully matched flags to bombs
			//and if all other tiles have been clicked open
			if((coverGrid[i][j] == 11 && grid[i][j].id == 9) || (coverGrid[i][j] == grid[i][j].id)) {
				count++;
			}
		}
	}
	//if user has accounted for all tiles correctly, they have won
	return count == rows * cols;
}

void GuiGrid::resetGrid() {
	//reset cover tiles to plain tile image
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			coverGrid[i][j] = 10;
		}
	}
	//generate a new board using MsGame object

	game.initializeBoard();
	this-> grid = game.getBoard();
}


//getter methods
Sprite GuiGrid::getTiles() {
	return tiles;
}

std::vector<std::vector<int> > GuiGrid::getGrid() {
	return coverGrid;
}

Sprite GuiGrid::getSmilies() {
	return smilies;
}

int GuiGrid::getSquareSize() {
	return sSize;
}

std::pair<int, int> GuiGrid::getSmileNums() {
	return smNums;
}

int GuiGrid::getSmileSizeX() {
	return smSizeX;
}

int GuiGrid::getSmileSizeY() {
	return smSizeY;
}

//setter methods
void GuiGrid::setSquareSize(int s) {
	this->sSize = s;
}

void GuiGrid::setSmileSizes(int x, int y) {
	this->smSizeX = x;
	this->smSizeY = y;
}

void GuiGrid::setSmileNums(int x, int y) {
	this->smNums.first = x;
	this->smNums.second = y;
}


int GuiGrid::writeLeader(std::string TimeData){
	std::ofstream outfile;
   	outfile.open("leader.txt");
   	for(int i=0; i<1; i++){
   		outfile << TimeData << "\n";
   	}
	//outfile << "writeeeee\n";
	outfile.close();
	return 0;
}
	

int GuiGrid::main() {

	srand(time(NULL));

	//anything less than 3x3 will look wrong...

	//pixel dimensions for each smiley, so they line up
	std::vector<std::pair<float, float>> smilies = {{146/2, 147/2}, {146/2 + 4, 147/2 + 4}, {146/2, 147/2}, {146/2 + 4, 147/2 + 4}};
	
	//create GuiGrid object
	GuiGrid test(rows, cols, numOfBombs);

	//get appropriate dimensions
	int sSize = test.getSquareSize();
	unsigned int smX = test.getSmileSizeX();
	unsigned int smY = test.getSmileSizeY();
	
	//create window large enough to contain specified number of rows/cols
	//made so has no resizing capabilities
	RenderWindow app(VideoMode(rows * sSize, cols * sSize + smY),"Beginner", Style::Titlebar | Style::Close);

	
	Vector2u wSize = app.getSize();

	//convert from unsigned int to float for Text.setPosition
	float ScaleX = (float) wSize.x;

	//create Time object;
	//when passing Time object as argument, it gets messed up so just worte entire thing here
	
	Font timerFont, bombFont;

	if(!timerFont.loadFromFile("digital-7.ttf")){
		//err
	}
	if(!bombFont.loadFromFile("digital-7.ttf")){
		//err
	}




	Text timerText_S, timerText_M, Bombs;
	Clock clock;
	Time time = clock.getElapsedTime();
	timerText_S.setFont(timerFont);
	timerText_M.setFont(timerFont);
	timerText_S.setPosition(ScaleX/4.5, 1);
	timerText_M.setPosition(ScaleX/20, 1);

	timerText_S.setCharacterSize(ScaleX/9);
	timerText_M.setCharacterSize(ScaleX/9);

	int bombnum = numOfBombs;
	std::ostringstream ss_B;
	ss_B << numOfBombs;
   	Bombs.setString(ss_B.str().c_str());
	
	Bombs.setFont(bombFont);
	Bombs.setPosition(ScaleX-(ScaleX/4),1);
	Bombs.setCharacterSize(ScaleX/9);

	SoundBuffer buffer;

	if(!buffer.loadFromFile("clickSound.wav")){
		//err
	}

	Sound sound;
	sound.setBuffer(buffer);

	//do stuff until the window is closed
	while(app.isOpen()) {

		int t = 0;
		//track events that occur
		Event e;	
		while(app.pollEvent(e)) {

			//close window if x is clicked
			if(e.type == Event::Closed) {
				app.close();
			}

			//if the mouse button is clicked, call Clicked	
			if(e.type == Event::MouseButtonReleased) {
				if(!test.hasWon() && !test.hasLost) {
					t = test.Clicked(e);
						
				//check that mouse is clicking within bounds of smiley face
				//only allow this if user has lost/won
				} else if((unsigned)e.mouseButton.y <= smY && ((unsigned)e.mouseButton.x <= (wSize.x/2 + smX/2) && (unsigned)e.mouseButton.x >= (wSize.x/2 - smX/2))){
					//create a new game
					test.setSmileNums(0, 0);
					//test.resetGrid();
					app.close();
					test.main();
					test.hasLost = false;	
					std::ostringstream ss_B;
					ss_B << bombnum;
					Bombs.setString(ss_B.str().c_str());
				}
			} else if(e.type == Event::MouseButtonPressed) {
				sound.play();
				if(!test.hasWon() && !test.hasLost) {
					test.setSmileNums(1, 0);
				}
			}
			//if user clicks on a bomb, they have lost
			if(t == 9) {
				test.revealBoard();
				test.setSmileNums(1,1);
				test.hasLost = true;
				numOfBombs= 0;
				std::ostringstream ss_B;
				ss_B << numOfBombs;
				Bombs.setString(ss_B.str().c_str());
				

			//otherwise check if they've won
			} else if(test.hasWon() && !test.hasLost) {
				test.revealBoard();
				test.setSmileNums(0, 1);


			// Count Bomb
			} else if (e.type == Event::MouseButtonPressed && test.flagOnBomb(e)){
				numOfBombs--;
				std::ostringstream ss_B;
				ss_B << numOfBombs;
				Bombs.setString(ss_B.str().c_str());
			}

		}

		//clears the screen - won't see what was drawn underneath	
		Color color(192, 192, 192);
		app.clear(color);
	
		Sprite tiles = test.getTiles();
		int sSize = test.getSquareSize();
		//get current state of the coverGrid
		std::vector<std::vector<int> > topGrid = test.getGrid();
		
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				//chooses appropriate part of texture
				tiles.setTextureRect(IntRect(topGrid[i][j] * sSize, 0, sSize, sSize));
				//sets the position of the individual tile
				tiles.setPosition(i * sSize, j * sSize + smY);
				//draws each tile as it progresses through loop
				app.draw(tiles);
			}
		} 
		std::pair<int, int> smNums = test.getSmileNums();
		Sprite smiley = test.getSmilies();
		//select current smiley face from image loaded in constructor
		smiley.setTextureRect(IntRect(smNums.first * smilies[smNums.first].first, smNums.second * smilies[smNums.second].second, smX, smY));
		//place smiley face on top middle of window
		smiley.setPosition((wSize.x - smX)/2, 0);
		app.draw(smiley);

		//Time generate
		if(!test.hasWon() && !test.hasLost) {
			time = clock.getElapsedTime();
			std::ostringstream ss_S, ss_M;
			int seconds = time.asSeconds();
			ss_S << seconds % 60;
			ss_M << seconds / 60;

			timerText_S.setString(ss_S.str().c_str());
			timerText_M.setString(ss_M.str().c_str());
		}

		//display time
		app.draw(timerText_S);
		app.draw(timerText_M);
		app.draw(Bombs);
		//displays entire screen (what has been rendered so far)
		app.display(); 
	}
	return 0;
}
