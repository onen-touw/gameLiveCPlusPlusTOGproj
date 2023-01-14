
#include<SDL.h>
#include<SDL_image.h>

#include <iostream>

#include"baseGameClass.h"
#include "fieldClass.h"
#include"imageClass.h"


int main(int argc, char* argv[]) {

	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
	baseGameClass baseGame;

	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
	imageClass imageTest;
	imageTest.loadImages();
	imageTest.logOut();

	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
	fieldClass fieldTest;

	

	//fieldTest.blit(imagesNames::bushWithoutBerryCellHouseArea, 0, 0);


	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 

	if (baseGame.initModuls())
	{
		fieldTest.createFieldV();
		fieldTest.generationObjects();
		fieldTest.blitField();
		SDL_UpdateWindowSurface(gameSettings::win);

		std::cout << "ready\n";
		SDL_Event event;
		bool game = true;
		bool firstHouse = false;
		bool h = false;
		int cursor_X = 0, cursor_Y = 0;


		while (game)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
				{
					game = false;
				}

				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
					fieldTest.transmitField(directions::right);
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
				{
					fieldTest.transmitField(directions::up);
				}
				else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
				{
					fieldTest.transmitField(directions::left);
				}
				else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
				{
					fieldTest.transmitField(directions::down);
				}

				if (!firstHouse)
				{
					if (event.type == SDL_MOUSEMOTION)
					{
						fieldTest.blitField();
						cursor_X = event.motion.x; cursor_Y = event.motion.y;
						if (cursor_Y > gameSettings::winObjSize.menuHeader)
						{
							h = fieldTest.chosePositionForHouse({ (short int)cursor_X, (short int)cursor_Y });
							SDL_UpdateWindowSurface(gameSettings::win);
						}
					}
					if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP && h)
					{
						std::cout << "ok\n";
						//SDL_GetMouseState(&cursor_X, &cursor_Y);
						fieldTest.setHouse({ (short)cursor_X,(short)cursor_Y });
						
						fieldTest.blitField();
						SDL_UpdateWindowSurface(gameSettings::win);
						firstHouse = true;
					}


				}
				/*SDL_Rect mt = { 50,50,100,100 };
			
				SDL_BlitScaled(gameSettings::imageVector[imagesNames::emptyCell], NULL, gameSettings::surface, &mt);
				SDL_UpdateWindowSurface(gameSettings::win);*/
			/*	fieldTest.blit(imagesNames::bushWithoutBerryCellHouseArea, 0, 0);

				SDL_UpdateWindowSurface(gameSettings::win);*/
				SDL_Delay(1000 / 60);
			}
		}
	}
	else
	{
		std::cout << "problemm\n";
	}
	

	

	return 0;
}
