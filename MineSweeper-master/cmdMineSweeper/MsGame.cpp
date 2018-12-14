#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstring>
#include "MsGame.hpp"

/*
Constructor for MsGame object called from main.
There should only be one of these objects instantiated at a time.
sizeX and sizeY are the user"s input dimensions
board is a 2D vector originally initialized with cells that all believe they are at the position (0,0) 
	and are not bombs until initializeBoard is called.
*/
MsGame::MsGame(int boardSizeX, int boardSizeY, int numberOfBombs, const char* fileName, time_t start_time) { 
	this->sizeX = boardSizeX;
	this->sizeY = boardSizeY;
	this->bombs = numberOfBombs;
	this->fileName = fileName;
	this->start_time = start_time;
	
	this->board = std::vector<std::vector<MsCell> >(this->sizeX, std::vector<MsCell>(this->sizeY, MsCell(0,0,false)));

	//Randomly fills board with bombs and determines the number of adjacent bombs each cell has.
	initializeBoard();
}

/*
Called from intializeBoard 
iterates over each cell in board to determine the number of adjacent bombs each cell has
this number is stored in cell->bombNeighbors
*/
void MsGame::findBombNeighbors(){
	for (int i = 0; i < this->sizeX; i++){
		for (int j = 0; j < this->sizeY; j++){
			countNeighbors(i,j);
		}
	}
	return;
}

/*
Called from MsGame constructor to initialize a newly constructed board (2D vector).
If over half of the cells will be bombs, the function will fill board will bombs than randomly
	change the correct number of bombs to safe spaces so that the end result is the user"s input number of bombs.
If under half the cells will be bombs, the function will change the number of spaces specified
	by the user from  safe	spaces to bombs.
Then determines the number of adjacent bombs to each cell.
Assumes rand has been seeded in main

bombCell and safeCell are names for MsCell objects with isBomb set to false and true
	respectively
*/
void MsGame::initializeBoard(){
	
	bool moreThanHlafBombs = false;
	int inputBombs = this->bombs;
	int cellChanges = inputBombs;
	
	//check if more than half of the spaces will be bombs
	if (inputBombs > this->sizeX * this->sizeY) {
		
		//if over half bombs, fill all cells with bombs
		for (int i = 0; i < this->sizeX; i++) {
			for (int j = 0; j < this->sizeY; j++) {
				MsCell bombCell(i,j,1);
				this->board[i][j] = bombCell;
			}
		}
		cellChanges = ((this->sizeX * this->sizeY) - inputBombs);
		moreThanHlafBombs = true;
	}
	
	//randomly change the correct number of cells
	for (int i = 0; i < cellChanges; i++) {
		int rndX = std::rand() % this->sizeX;
		int rndY = std::rand() % this->sizeY;
		
		//changes bombs to safe cells
		if (moreThanHlafBombs) {
			if (this->board[rndX][rndY].isBomb() == 1) {
				MsCell safeCell(rndX,rndY,0);
				this->board[rndX][rndY] = safeCell;
			} else {
				i--;
				continue;
			}
		
		// changes safe cells to bombs
		} else {
			if (this->board[rndX][rndY].isBomb() == 0) {
				MsCell bombCell(rndX,rndY,1);
				this->board[rndX][rndY]= bombCell;
			} else {
				i--;
				continue;
			}
		}
	}

	//initialize cell->bombNeighbors and print board
	findBombNeighbors();
	printBoard();
	std::cout << std::endl;
	return;
}

/*
Called from step whenever a cell is opened.
Recursive function that searches all neighboring MsCells and opens all that do not have any 
	adjacent bombs and all cells that have adjacent bombs on the perimeter of the ones 
	that were just opened.
*/
void MsGame::flood(int i, int j){
	if ((this->board[i][j].isOpen() == 0) & (this->board[i][j].getBombNeighbors() == 0)){
		this->board[i][j].setOpen(1);
		for (int a = -1; a < 2; a++){
			for (int b = -1; b < 2; b++){
				if (((i+a > -1) & (j+b > -1)) & ((i+a < this->sizeX) & (j+b < this->sizeY))){
					this->flood(i+a, j+b);
				}
			}
		}
	}
	
	//opens perimeter of cells that do not have a bombNeighbors count of 0.
	if (this->board[i][j].getBombNeighbors() != 0) this->board[i][j].setOpen(1);

	return;
}

/*
Step function called by main to update board after each move.

Prompts user for the position of where they would like to make a move and checks if it is possible
Prompts user for command ("f" - flag, "o" - open, "?" - make question mark) and currently does not check
	if it is a valid operation.
	
If the command is f:
	toggles cell->flag to false or true depending on its state when called
	done by calling MsCell->setFlag()
If the command is o:
	checks if cell has already been opened
	returns 0 if the cell is a bomb, causing the player to lose the game
	otherwise opens cell and calls flood to check if there are no adjacent bombs
If the command is ?:
	toggles cell->question to false or true depending on its state when called
	done by calling MsCell->setQuestion()
	
Iterates over entire board to check if all safe cells are open and all bomb cells are flagged.
	If all conditions are met for the player to win the game, the function returns 1 and the 
	board is revealed by calling revealBoard.
If not all conditions to win are correct, the current state of the board is printed and returns a
	value of 1.
*/
int MsGame::step() {
	int boardX, boardY;
	std::string cmd;
	
	//get cell position
	std::cout << "Please enter the position of your move (row column): ";
	std::cin >> boardX >> boardY;
	while (!std::cin || (boardX < 0) || (boardX > this->sizeX) || (boardY < 0) || (boardY > this->sizeY)){
		std::cout << "Incorrect input.\nPlease enter the position of your move (row column): ";
		std::cin.clear();
		std::cin.ignore(256,'\n');
		std::cin >> boardX >> boardY;
		std::cout << "\n";
	}
	std::cout << std::endl;

	MsCell cell = this->board[boardX][boardY];
	
	//get input command
	std::cout << "Please enter the command for your move (f, o, ?): ";
	std::cin >> cmd;
	while ((cmd != "f") & (cmd != "o") & (cmd != "?")){
		std::cout << "Incorrect input.\nPlease enter the command for your move (f, o, ?): ";
		std::cin >> cmd;
		std::cout << "\n";
	}
	std::cout << std::endl;
	
	//execute input command
	if (cmd == "f"){
		if (cell.isFlagged() == 1){
			this->board[boardX][boardY].setFlag(0);
		}
		else if (cell.isOpen() == 1){
			std::cout << "You cannot flag an open cell.\n" << std::endl;
		}
		else{
			this->board[boardX][boardY].setFlag(1);
		}
	}
	
	else if (cmd == "o"){
		if (cell.isOpen() == 1)
			std::cout << "Cell has already been revealed." << std::endl;
		else{
			if(cell.isBomb() == 1){
				std::cout << "You Lose!" << std::endl;
				this->revealBoard();
				return 0;
			}
			if (this->board[boardX][boardY].getBombNeighbors() != 0) this->board[boardX][boardY].setOpen(1);
			else this->flood(boardX, boardY);
		}
	}
	
	else if (cmd == "?"){
		if (cell.isQuestion() == 1)
			this->board[boardX][boardY].setQuestion(0);
		else if (cell.isOpen() == 1){
			std::cout << "You cannot flag an open cell.\n" << std::endl;
		}
		else
			this->board[boardX][boardY].setQuestion(1);
	}
	
	//check if the player has won
	int correctCounter = 0;
	for (int i = 0; i < this->sizeX; i++) {
		for (int j = 0; j < this->sizeY; j++) {
			cell = this->board[i][j];
			
			if ((cell.isBomb() == 1) && (cell.isFlagged() == 1))
				correctCounter++;
			if ((cell.isBomb() == 0)  && (cell.isOpen() == 1))
				correctCounter++;
		}
	}
	if (correctCounter == this->sizeX * this->sizeY){
		time_t end_time = std::time(NULL);
		std::cout << "You Won!!" << std::endl;
		this->revealBoard();
		updateLeaderFile(end_time);
		return 0;
	}
	
	//print if player has not won or lost
	this->printBoard();
	return 1;
}

/* 
Called from step after each move is made (except when player wins)
Also prints column number and row number as the first row and column respectively
Prints cells by calling MsCell->printCell()
*/
void MsGame::printBoard(){
	for (int i = 0; i<this->sizeX+1; i++){
		for (int j = 0; j < this->sizeY+1; j++){
			//print first row
			if (i == 0){
				if (j == 0) std::cout << "   ";
				else if ((j > 0) && (j < 10)) std::cout << j-1 << "  ";
				else std::cout << j-1 << " ";
				if (j == this->sizeY){
					std::cout << std::endl;
				}
			}
			//print first column
			else if ((j == 0) & (i != 0)){
				std::cout << i - 1 << " ";
				if (i < 11) std::cout << " ";
			}
			//print cells
			else{
				this->board[i-1][j-1].printCell();
				std::cout << "  ";
				//if (j > 9) std::cout << " ";
				if (j == this->sizeY){
					std::cout << std::endl;
				}
			}
		}
	}
	std::cout << std::endl;
	return;
}

/*
Called from step when the player wins or looses the game.
Iterates over entire board and prints
column and row number
x if the cell is a bomb
bombNeighbors if the cell is not a bomb

cells are printed by calling MsCell->printCell()
*/
void MsGame::revealBoard(){
	for (int i = 0; i<this->sizeX;i++){
		for (int j = 0; j < this->sizeY; j++){
			if (this->board[i][j].isBomb() == 1){
				this->board[i][j].setSymbol("x");
			}
			else if (this->board[i][j].getBombNeighbors() != 0){
				this->board[i][j].setOpen(1);
			}
			this->board[i][j].printCell();
			std::cout << " ";
			if (j > 9) std::cout << " ";
			if (j == this->sizeY - 1){
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
	return;
}

/*
Called from findBombNeighbors which is called from initializeBoard
searches all adjacent cells to the position passed and counts the 
	number of those cells that are bombs
After counting bombs, MsCell->setNeighborCount() is called for the cell
	at the position passed
*/
void MsGame::countNeighbors(int i, int j){
	int count = 0;

	for(int a = -1; a < 2; a++){
		for (int b = -1; b < 2; b++){
			if (((i+a > -1) & (j+b > -1)) & ((i+a < this->sizeX) & (j+b < this->sizeY))){
				if (!((a == 0) & (b == 0)) & (this->board[i+a][j+b].isBomb() == 1)){
					count++;
				}
			}
		}
	}
	this->board[i][j].setNeighborCount(count);
	return;
}

/*
Called from step after the player has won the game.
This function takes the input file, reads all lines from Beginner, Intermediate and Expert and puts the names and scores into the respective b,i and e NameScore vectors. Then determines if the player is playing beginner, intermediate or expert level, then inserts their score into the corresponding list if they have made the top ten. The function then clears the input file and rewrites the new leader board stored in the three vectors. During this step, the function also prints the updated leader board to the user.
*/

void MsGame::updateLeaderFile(time_t end_time) {
	const char* checkName = "@@No File@@";
	if (std::strcmp(this->fileName,checkName) == 0) {
		return;
	} else {
		std::ifstream ifs;
		ifs.open(this->fileName);
		
		std::vector<std::vector<std::string> > bNameScore 
						(10, std::vector<std::string> (2, " "));
		std::vector<std::vector<std::string> > iNameScore 
						(10, std::vector<std::string> (2, " "));
		std::vector<std::vector<std::string> > eNameScore 
						(10, std::vector<std::string> (2, " "));
		
		bool beginner = false, intermediate = false, expert = false;
		int counter = -1;
		//loop through input file
		while (!ifs.eof()) {
			std::vector<std::string> split_line;
			std::string name, score;
			ifs >> name;
			
			if (name.compare("\n") == 0)
				continue;
			//determine which vector to put the information in
			else if ((name.compare("Beginner:") == 0) || (name.compare("Intermediate:") == 0) || (name.compare("Expert:") == 0)) {
				//do nothing
			} else
				ifs >> score;
		
			if (name.compare("Beginner:") == 0) {
				counter = -1;
				beginner  = true;
				continue;
			} else if (name.compare("Intermediate:") == 0) {
				counter = -1;
				beginner = false;
				intermediate  = true;
				continue;
			} else if (name.compare("Expert:") == 0) {
				counter = -1;
				intermediate = false;
				expert  = true;
				continue;
			} else {
				if (counter > 9)
					continue;
				counter++;
				split_line.push_back(name);
				split_line.push_back(score);
			}
			
			//insert old leader board into respective lists
			if (beginner){
				bNameScore.insert(bNameScore.begin() + counter, split_line);
			} else if (intermediate){
				iNameScore.insert(iNameScore.begin() + counter, split_line);
			} else if (expert) {
				eNameScore.insert(eNameScore.begin() + counter, split_line);
			}
		}
		ifs.close();
		
				
		char difficulty;
		std::vector<std::vector<std::string> > changeVector;
		
		//check if player is playing one of the predefined sizes and bomb number
		if ((this->sizeX == 8) && (this->sizeY == 8) && (this->bombs == 1)){
			difficulty = 'b';
			changeVector = bNameScore;
		}
		else if ((this->sizeX == 16) && (this->sizeY == 16) && (this->bombs == 40)){
			difficulty = 'i';
			changeVector = iNameScore;
		}
		else if ((this->sizeX == 16) && (this->sizeY == 31) && (this->bombs == 99)){
			difficulty = 'e';
			changeVector = eNameScore;
		} else {
			difficulty = 'c';
			return;
		}
		
		double playerScore = difftime(end_time, start_time);
		std::string playerName;
		
		//print player"s score
		std::cout << "Your time was: " << playerScore << " seconds!" << std::endl;
		std::cout << "Please enter your name: ";
		std::cin >> playerName;

		
		//convert player score to string
		std::string playerScoreStr;
		std::ostringstream ss;
		ss << playerScore;
		playerScoreStr = ss.str();
		
		//create vector of name and score
		std::vector<std::string> newEntry;
		newEntry.push_back(playerName);
		newEntry.push_back(playerScoreStr);
		
		//insert new entry into correct place in corresponding list from old leader board
		counter = -1;
		for(auto& row:changeVector) {
			counter++;
			if (row[1].compare(" ") == 0){
				counter--;
				continue;
			}
			int leaderScore = std::stoi( row[1] );
			if (leaderScore < playerScore)
				continue;
			else {
				if (changeVector.size() == 10)
					changeVector.pop_back();
				changeVector.insert(changeVector.begin() + counter, newEntry);
				break;
			}
		}
		
		//check edge cases
		if (changeVector.size() == 0)
			changeVector.push_back(newEntry);
		
		if (changeVector[counter][1].compare(" ") != 0) {
			if ((std::stoi(changeVector[counter][1]) < playerScore) && (changeVector[0][1] != " ")){
				changeVector.insert(changeVector.begin() + counter +1, newEntry);
			}
		}
		
		std::ofstream ofs;
		ofs.open(this->fileName, std::ofstream::out | std::ofstream::trunc);
		
		std::string name, score;
		//write the new vectors to the file
		std::cout << "Leader Board:" << std::endl;
		ofs << "Beginner:" << "\n";
		int outCounter = -1;
		if (difficulty == 'b') {
			std::cout << "\nBeginner: " << std::endl;
			for(auto& row:changeVector) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
				std::cout << name << " " << score << std::endl;
			}
		} else {
			for(auto& row:bNameScore) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
			}
		}
		ofs << "Intermediate: " << "\n";
		if (difficulty == 'i') {
			std::cout << "Intermediate: " << std::endl;
			for(auto& row:changeVector) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
				std::cout << name << " " << score << std::endl;
			}
		} else {
			for(auto& row:iNameScore) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
			}
		}
		ofs << "Expert: " << "\n";
		if (difficulty == 'e') {
			std::cout << "Expert: " << std::endl;
			for(auto& row:changeVector) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
				std::cout << name << " " << score << std::endl;
			}
		} else {
			for(auto& row:eNameScore) {
				if (row[1].compare(" ") == 0)
					continue;
				outCounter++;
				if (outCounter > 9) {
					outCounter = -1;
					break;
				}
				name = row[0];
				score = row[1];
				ofs << name << " " << score << "\n";
			}
		}
		ofs.close();
	
	}
	return;
}
