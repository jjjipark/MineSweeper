#include "menu.hpp"	

using namespace sf;

Menu::Menu(float width, float height)
{
	
	if(!font.loadFromFile("digital-7.ttf")){
		//error
	}

//	if(!background.loadFromFile("background.png")){
		//err
//	}
	
	Color color(192,192,192);

	text[2].setFont(font);
	text[2].setString("MineSweeper");
	text[2].setCharacterSize(85);
	text[2].setFillColor(Color::White);
	text[2].setPosition(60, 80);
	
	text[0].setFont(font);
	text[0].setString("Play");
	text[0].setFillColor(Color::Red);
	text[0].setPosition(200,260);
	text[0].setCharacterSize(50);

	//menu[0].setPosition(Vector2f(width/2, height/(NUMBER_OF_MENU +1) *1));
	//menu[0].setFillColor(Color::Black);
	menu[0].setSize(Vector2f(120,60));
	menu[0].setPosition(180,260);
	menu[0].setFillColor(color);

	text[1].setFont(font);
	text[1].setString("Exit");
	text[1].setFillColor(Color::White);
	text[1].setPosition(210, 340);
	text[1].setCharacterSize(50);

	//menu[1].setFillColor(Color::Black);
	menu[1].setSize(Vector2f(120, 60));

	//menu[1].setPosition(Vector2f(width/2, height/(NUMBER_OF_MENU +1) *2));
	menu[1].setPosition(190, 340);
	menu[1].setFillColor(color);

}

Menu::~Menu(){
}

void Menu::draw(RenderWindow &window){
	for(int i=0; i< NUMBER_OF_MENU; i++){
		//window.draw(Title);
		//window.draw(background);
		window.draw(menu[i]);
		window.draw(text[i]);
	}
}

int Menu::MouseOnPlay(int mX, int mY){
	if ((mX > menu[0].getPosition().x) && (mX < menu[0].getPosition().x+ menu[0].getSize().x) && ( mY < menu[0].getPosition().y + menu[0].getSize().y) && mY > (menu[0].getPosition().y)){
		//text[0].setFillColor(Color::Green);
		return 1;
	}
	return 0;
}

int Menu::MouseOnExit(int mX, int mY){

	if ((mX > menu[1].getPosition().x) && (mX < menu[1].getPosition().x+ menu[1].getSize().x) && ( mY < menu[1].getPosition().y + menu[1].getSize().y) && mY > (menu[1].getPosition().y)){
		return 1;
	}
	return 0;
}


void Menu::changePlayColor(){
	text[0].setFillColor(Color::Green);
}

void Menu::changeExitColor(){
	text[1].setFillColor(Color::Green);
}

void Menu::PlayColorBack(){
	text[0].setFillColor(Color::Red);
}

void Menu::ExitColorBack(){
	text[1].setFillColor(Color::White);
}
	
