
#include<SDL.h>
#include<SDL_image.h>

#include <iostream>

#include"baseGameClass.h"


int main(int argc, char* argv[]) {

	///TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
	baseGameClass baseGame;

	if (baseGame.initModuls())
	{
		
		std::cout << "ready\n";
	}
	SDL_Event event;
	bool game = true;
	while (game)
	{


		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)//������������ �������� ���� ����� ������ "�����"
			{
				game = false;
			}
			SDL_UpdateWindowSurface(gameSettings::win);
		}
	}

	

	return 0;
}
