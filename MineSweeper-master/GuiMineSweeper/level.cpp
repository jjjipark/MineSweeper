#include "SFML/Graphics.hpp"
#include <iostream>

#include "level.hpp"
#include "GuiGrid.hpp"

using namespace sf;

Level::Level(float width, float height){
	if(!font.loadFromFile("square.ttf")){
		//err
	}
	
//	if(!background.loadFromFile("background.png")){
		//err
//	}
	Color color(192,192,192);

	text[0].setFont(font);
	text[0].setString("Beginner");
	text[0].setCharacterSize(40);
	text[0].setFillColor(Color::Green);
	text[0].setPosition(width/4, height/3);
	
	label[0].setSize(Vector2f(300,50));
    	label[0].setPosition(width/4, height/3);
    	label[0].setFillColor(color);

	text[1].setFont(font);
    	text[1].setString("Intermediate");
    	text[1].setCharacterSize(40);
    	text[1].setFillColor(Color::Green);
    	text[1].setPosition( width/5, height/2);

	label[1].setSize(Vector2f(300,50));
  	label[1].setPosition(width/4, height/2);
    	label[1].setFillColor(color);

	text[2].setFont(font);
        text[2].setString("Advanced");
        text[2].setCharacterSize(40);
        text[2].setFillColor(Color::Green);
        text[2].setPosition( width/4, height/2+height/6);

	label[2].setSize(Vector2f(300,50));
        label[2].setPosition(width/4, height/2+ height/5);
        label[2].setFillColor(color);

/*
        text[3].setFont(font);
	text[3].setString("Leader Board");
	text[3].setCharacterSize(40);
	text[3].setFillColor(Color::Green);
	text[3].setPosition(width/4, height/2 + height/3);
	
	label[3].setSize(Vector2f(300,50));
*/

}

Level::~Level(){
}

void Level::draw(RenderWindow &window){
	for(int i=0; i<NUMBER_OF_LEVEL; i++){
		//window.draw(text[i]);
		window.draw(label[i]);
		//window.draw(text[i]);
	}
	for(int i=0; i<NUMBER_OF_LEVEL; i++){
		window.draw(text[i]);
	}
}


int Level::MouseOnBeginner(int mX, int mY){
	if((mX > label[0].getPosition().x) && (mX < label[0].getPosition().x + label[0].getSize().x) && ( mY < label[0].getPosition().y + label[0].getSize().y ) && (mY > label[0].getPosition().y)){
		return 1;
	}
	return 0;
}

int Level::MouseOnIntmd(int mX, int mY){
        if((mX > label[1].getPosition().x) && (mX < label[1].getPosition().x + label[1].getSize().x) && ( mY < label[1].getPosition().y + label[1].getSize().y ) && (mY > label[1].getPosition().y)){
                return 1;
        }
        return 0;
}


int Level::MouseOnAdv(int mX, int mY){
        if((mX > label[2].getPosition().x) && (mX < label[2].getPosition().x + label[2].getSize().x) && ( mY < label[2].getPosition().y + label[2].getSize().y ) && (mY > label[2].getPosition().y)){
                return 1;
        }
        return 0;
}

int Level::MouseOnLeader(int mX, int mY){
        if((mX > label[3].getPosition().x) && (mX < label[3].getPosition().x + label[3].getSize().x) && ( mY < label[3].getPosition().y + label[3].getSize().y ) && (mY > label[3].getPosition().y)){
                return 1;
        }
        return 0;
}

int Level:: main(){
	RenderWindow level_window(VideoMode(500,500), "Main Menu");
	Level Level(level_window.getSize().x, level_window.getSize().y);
	RenderWindow tempWindow;

//	Leader leader(500,500);
	const int Bomb_B = 10;
	const int Bomb_I= 40;
	const int Bomb_A = 99;

	GuiGrid test_B(8, 8, Bomb_B);
	GuiGrid test_I(16, 16, Bomb_I);
	GuiGrid test_A(16, 31, Bomb_A);

	SoundBuffer buffer;

	if(!buffer.loadFromFile("clickSound.wav")){
		//err
	}

	Sound sound;
	sound.setBuffer(buffer);

	while(level_window.isOpen()){
		Vector2i pos = Mouse::getPosition(level_window);
		int mX = pos.x;
		int mY = pos.y;
		
		Event e;
		while( level_window.pollEvent(e)){
			if(e.type == Event::Closed)
				level_window.close();
			if(e.type == Event::MouseButtonPressed){
				sound.play();
				if(Level.MouseOnBeginner(mX, mY)==1){
					//tempWindow.create(VideoMode(600,600), "button works");
					level_window.close();
					test_B.main();
				}
				else if (Level.MouseOnIntmd(mX, mY) == 1){
					level_window.close();
                    			test_I.main();
				}

				else if (Level.MouseOnAdv(mX, mY)==1){
                    			level_window.close();
                    			test_A.main();
				}

				/*
				else if (Level.MouseOnLeader(mX, mY) == 1){
					level_window.close();
					//tempWindow.create(VideoMode(600,600), "button works");
					leader.main();
					while(tempWindow.isOpen()){
						Event e;
						while(tempWindow.pollEvent(e)){
                       					if(e.type== Event::Closed)
                           					tempWindow.close();
                        			}

					}

				}*/

			}
		}
			Color color(192,192,192);
			level_window.clear(color);
			Level.draw(level_window);
			level_window.display();
			tempWindow.display();
	}
	return 0;
}

	




