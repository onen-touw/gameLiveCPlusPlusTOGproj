
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

	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
	/*fieldClass fieldTest;

	fieldTest.createFieldV();
	fieldTest.blit();*/


	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 

	if (baseGame.initModuls())
	{
		
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

				SDL_Rect mt = { 50,50,100,100 };
			
				SDL_BlitScaled(imageTest.getImage(imagesNames::emptyCell), NULL, gameSettings::surface, &mt);
				SDL_UpdateWindowSurface(gameSettings::win);
			}
		}
	}
	else
	{
		std::cout << "problemm\n";
	}
	

	

	return 0;
}
