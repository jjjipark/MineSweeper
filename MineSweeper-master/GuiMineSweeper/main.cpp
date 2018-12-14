#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "menu.hpp"
#include "GuiGrid.hpp"
#include "level.hpp"

using namespace sf;

int main(){
	
	RenderWindow main(VideoMode(500,500), "Main Menu");
	RenderWindow window;

	Menu menu(500, 500);
	//Level level(main.getSize().x, main.getSize().y);
	Level level(500,500);
	
	//display bomb image
	Texture bomb;
	
	Sprite bombImage1;
	Sprite bombImage2;

	if(!bomb.loadFromFile("bomb.png")){
		//err
	}

	bombImage1.setTexture(bomb);
	bombImage1.setScale(3,3);
	bombImage1.setPosition(60,160);
	bombImage2.setTexture(bomb);
	bombImage2.setScale(3,3);
	bombImage2.setPosition(300,300);

	//Set sound
	SoundBuffer buffer;
//	if(!buffer.loadFromFile("clickSound.wav")){
		//err
//	}
	buffer.loadFromFile("clickSound.wav");
	Sound sound;
	sound.setBuffer(buffer);
	
	while (main.isOpen()){
		Vector2i pos = Mouse::getPosition(main);
		int mX = pos.x;
		int mY = pos.y;
		
		Event event;
		while(main.pollEvent(event)){
			if(event.type== Event::Closed)
                main.close();
			if(event.type == Event::MouseButtonPressed){
				sound.play();
				if (menu.MouseOnPlay(mX, mY) ==1 ){
					main.close();
					//game.main();
					level.main();	
					/*	
					while(window.isOpen()){
						Event e;
						while(window.pollEvent(e)){
                       					if(e.type== Event::Closed)
                           					window.close();
						}	
					}*/
				}

				if(menu.MouseOnExit(mX,mY)==1 ){
					main.close();
				}
			}
			if (menu.MouseOnPlay(mX, mY) == 1){
				menu.changePlayColor();
			}
			if (menu.MouseOnPlay(mX, mY) == 0){
				menu.PlayColorBack();
			}
			if (menu.MouseOnExit(mX,mY) == 1){
				menu.changeExitColor();
			}
			if (menu.MouseOnExit(mX, mY) == 0){
				menu.ExitColorBack();
			}
			
		}	
		Color color(192, 192, 192);
		main.clear(color);
		//main.draw(backgroundImage);
		main.draw(bombImage1);
		main.draw(bombImage2);
		menu.draw(main);
		main.display();
		window.display();
	}
	
}

	
