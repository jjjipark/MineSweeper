#ifndef MSCELL_HPP_
#define MSCELL_HPP_
#include <string>

class MsCell {
	public:
		//Constructor and Destructor
		MsCell(int cellPosX, int cellPosY, int isBomb);
		~MsCell() {}
		
		//Getters
		int isBomb();
		int isOpen();
		int isFlagged();
		int isQuestion();
		int getX();
		int getY();
		int getBombNeighbors();
		
		//Setters
		void setOpen(int isOpen);
		void setFlag(int isFlagged);
		void setQuestion(int isQuestion);
		void setNeighborCount(int count);
		void setSymbol(std::string sym);

		void printCell();
		
	private:
		//Private Data
		std::string symbol;
		int posX, posY, bombNeighbors, bomb, open, question, flag;
};

#endif /* MSCELL_HPP_ */
