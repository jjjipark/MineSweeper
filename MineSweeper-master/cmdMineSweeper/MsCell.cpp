#include <iostream>
#include <string>
#include <sstream>
#include "MsCell.hpp"

/*
posX, posY,   - X and Y positions for cell in MsGame->board
bomb 		  - 0 if not a bomb, 1 if a bomb
bombNeighbors - number of adjacent cells that are bombs, initialized 
					from MsGame::countNeighbors
open 		  - 0 if closed, 1 if open
question      - 0 if not a question, 1 if it has been flagged as a question mark
flag 		  - 0 if not flagged, 1 if player has flagged it as a bomb
symbol 		  - Character that will be printed if printCell is called
				" " - open, 0 adjacent bombs
				int - open, int number of adjacent bombs
				"." - closed
				"*" - flagged
				"?" - question marked
				"x" - revealed bomb
*/
MsCell::MsCell(int cellPosX, int cellPosY, int isBomb){ 
	this->posX = cellPosX;
	this->posY = cellPosY;
	this->bomb = isBomb;
	this->bombNeighbors = 0;
	this->open = 0;
	this->question = 0;
	this->flag = 0;
	this->symbol = ".";
}

void MsCell::printCell(){
	std::cout << this->symbol;
	return;
}

int MsCell::isBomb(){
	return this->bomb;
}

int MsCell::isOpen(){
	return this->open;
}

int MsCell::isFlagged(){
	return this->flag;
}

int MsCell::isQuestion(){
	return this->question;
}

/*
Sets symbol to " " if no adjacent bombs
Sets symbol to number of adjacent bombs if not 0
changes open to input value
*/
void MsCell::setOpen(int openVal){
	if (this->bombNeighbors == 0){
		this->symbol = " ";
	}
	else{
		std::ostringstream ss;
		ss << this->bombNeighbors;
		this->symbol = ss.str();
	}
	this->open = openVal;
	return;
}

void MsCell::setFlag(int flagVal){
	if (flagVal == 1) this->symbol = "*";
	else this->symbol = ".";
	this->flag = flagVal;
	return;
}

void MsCell::setQuestion(int questionVal){
	if (questionVal == 1) this->symbol = "?";
	else this->symbol = ".";
	this->question = questionVal;
	return;
}

void MsCell::setNeighborCount(int count){
	this->bombNeighbors = count;
	return;
}

void MsCell::setSymbol(std::string sym){
	this->symbol = sym;
	return;
}

int MsCell::getX(){
	return this->posX;
}
int MsCell::getY(){
	return this->posY;
}
int MsCell::getBombNeighbors(){
	return this->bombNeighbors;
}