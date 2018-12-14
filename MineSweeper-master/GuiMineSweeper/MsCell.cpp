#include <iostream>
#include <string>
#include "MsCell.hpp"

MsCell::MsCell(int cellPosX, int cellPosY, int isBomb){ 
	this->posX = cellPosX;
	this->posY = cellPosY;
	this->bomb = isBomb;
	this->bombNeighbors = 0;
	this->open = 0;
	this->id = 0;
}

int MsCell::isBomb(){
	return this->bomb;
}

void MsCell::setNeighborCount(int count){
	this->bombNeighbors = count;
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
