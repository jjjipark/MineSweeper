#ifndef MSCELL_HPP_
#define MSCELL_HPP_

class MsCell {
	public:
		MsCell(int cellPosX, int cellPosY, int isBomb);
		~MsCell() {}
		
		//getters
		int isBomb();
		int getX();
		int getY();
		int getBombNeighbors();
		
		//setters
		void setNeighborCount(int count);

		int id;
		
	private:
		// Private data
		std::string symbol;
		int posX, posY, bombNeighbors, bomb, open;
};

#endif /* MSCELL_HPP_ */
