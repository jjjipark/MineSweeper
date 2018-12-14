***
CIS 330 Final Project
University of Oregon

MINESWEEPER

Programmers:
Laura Queen, Jonah Rose, Pallavi Webb, Jieun Park

Laura and Jonah worked on the command line version of Minesweeper, while Pallavi 
and Jieun were responsible for implementing the Gui version.

***

Rules of Minesweeper:
The object of the game is locate all the mines in on the board without revealing
any of them (getting blown up!). The first move is risky. You could open a mine 
immediately and lose, but if you don't you will learn valuable information. If 
the cell you chose has adjacent mines, the number of adjacent mines will be shown.
If the opened cell has no mine neighbors, the board will be flooded with open cells
until cells with mines as neighbors are reached. To win, you must flag all the mines 
and open all the safe cells. 

First, clone the 330-project bitbucket repository and then follow these instructions 
to play both our ASCII and GUI Minesweeper games:

ASCII:

cd 330-project/cmdMinesweeper	//move into the command line directory

make										//run the MakeFile

./cmdMinesweeper.exe						//run the executable



Gui MineSweeper:

You are required to download SFML 2.0 (not 1.6) before compiling. It should already be on ix-dev. 

cd 330-project/GuiMineSweeper				//move into the Gui directory

make										//run the MakeFile

./Game										//run the executable


Play the game and Enjoy!


