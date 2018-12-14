#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "MsGame.hpp"

MsGame::MsGame(int boardSizeX, int boardSizeY, const int numberOfBombs) { 
	this->sizeX = boardSizeX;
	this->sizeY = boardSizeY;
	this->bombs = numberOfBombs;
	this->board = std::vector<std::vector<MsCell> >(this->sizeX, std::vector<MsCell>(this->sizeY, MsCell(0,0,false)));

	initializeBoard();
}

MsGame::~MsGame(){
}

std::vector<std::vector<MsCell> > MsGame::getBoard() {
	return board;
}

void MsGame::findBombNeighbors(){
	for (int i = 0; i < this->sizeX; i++){
		for (int j = 0; j < this->sizeY; j++){
			countNeighbors(i,j);
		}
	}
}

//initialize a 2D vector Matrix randomly filled
//assumes rand has been seeded in main
/*
void MsGame::initializeBoard(){

	std::vector<std::vector<MsCell> > tempboard = std::vector<std::vector<MsCell> >(this->sizeX, std::vector<MsCell>(this->sizeY, MsCell(0,0,false)));
	

	for (int i = 0; i < this->sizeX; i++) {
		for (int j = 0; j < this->sizeY; j++) {
			int rnd = std::rand() % 100;

			if (rnd < 15) {
				MsCell bombCell(i,j,1);
				tempboard[i][j] = bombCell;
				this->board[i][j] = tempboard[i][j];
			}
			else  {
				MsCell safeCell(i,j,0);
				tempboard[i][j] = safeCell;
				this->board[i][j] = tempboard[i][j];

			}
		}
	}
	findBombNeighbors();
	return;
}*/


void MsGame::initializeBoard(){

	std::vector<std::vector<MsCell> > tempboard = std::vector<std::vector<MsCell> >(this->sizeX, std::vector<MsCell>(this->sizeY, MsCell(0,0,false)));
	
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
	return;
}

void MsGame::countNeighbors(int i, int j){
	int count = 0;

	for(int a = -1; a < 2; a++){
		for (int b = -1; b < 2; b++){
			if (((i+a > -1) & (j+b > -1)) & ((i+a < this->sizeX) & (j+b < this->sizeY))){
				if (!((a == 0) & (b == 0)) & (this->board[i+a][j+b].isBomb() == 1)){
					count++;
					board[i+a][j+b].id = 9;
				}
			}
		}
	}
	this->board[i][j].setNeighborCount(count);
	if(board[i][j].isBomb() == 1) {
		this->board[i][j].id = 9;
	} else {
		this->board[i][j].id = count;
	}
}

/*
std::vector<std::string> MsGame::split_str(std::string str) {
	std::vector<std::string> split_line;
	std::istringstream iss(str);
	for(std::string str; iss >> str; )
		split_line.push_back(str);
	return split_line;
}



void MsGame::updateLeaderFile(time_t end_time) {
	if (this->fileName == "@@No File@@") {
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
		while (!ifs.eof()) {
			std::vector<std::string> split_line;
			std::string name, score;
			ifs >> name;
			
			if (name.compare("\n") == 0)
				continue;
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
		
			if (beginner){
				bNameScore.insert(bNameScore.begin() + counter, split_line);
			} else if (intermediate){
				iNameScore.insert(iNameScore.begin() + counter, split_line);
			} else if (expert) {
				eNameScore.insert(eNameScore.begin() + counter, split_line);
			}
		}
		ifs.close();
		
		double playerScore = difftime(end_time, start_time);
		//std::string playerName;
		
		//std::cout << "Your time was: " << playerScore << " seconds!" << std::endl;
		//std::cout << "Please enter your name: ";
		//std::cin >> playerName;
		
		char difficulty;
		std::vector<std::vector<std::string> > changeVector;
		
		if ((this->sizeX == 8) && (this->sizeY == 8) && (this->bombs == 10)){
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
		}
		else
			difficulty = 'c';
		
		
		
		
		std::string playerScoreStr;
		std::ostringstream ss;
		ss << playerScore;
		playerScoreStr = ss.str();
		
		std::vector<std::string> newEntry;
		//newEntry.push_back(playerName);
		newEntry.push_back(playerScoreStr);
		
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
}*/
