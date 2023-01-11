
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
