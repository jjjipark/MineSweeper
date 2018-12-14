#ifndef MENU_H
#define MENU_H

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#define NUMBER_OF_MENU 4

using namespace sf;

class Menu
{

public:
	Menu(float width, float height);
	~Menu();

	void draw(RenderWindow &window);
	void MoveUP();
	void MoveDown();
	int MouseOnPlay(int mX, int mY);
	int MouseOnExit(int mX, int mY);
	void changePlayColor();
	void changeExitColor();
	void PlayColorBack();
	void ExitColorBack();	
private:
	
	Font font;
	Sprite button;
	Texture background;
		
	RectangleShape menu[NUMBER_OF_MENU];
	Text text[NUMBER_OF_MENU], Title;

};

#endif
