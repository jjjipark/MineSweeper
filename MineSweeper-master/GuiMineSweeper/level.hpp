#ifndef LEVEL_H
#define LEVEL_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#define NUMBER_OF_LEVEL 5

using namespace sf;

class Level
{

public:
	Level(float width, float height);
	~Level();
	
	
	void draw(RenderWindow &window);
	int MouseOnBeginner(int mX, int mY);
	int MouseOnIntmd(int mX, int mY);
	int MouseOnAdv(int mX, int mY);
	int MouseOnLeader(int mX, int mY);
	int main();	

private:
	Font font;
	
	RectangleShape label[NUMBER_OF_LEVEL];
	Text text[NUMBER_OF_LEVEL];

};

#endif
