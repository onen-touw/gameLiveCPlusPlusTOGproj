#pragma once

#include"settings.h"
#include <windows.h>

class baseGameClass
{
private:

	short int winWidth = 0;
	short int winHeight = 0;
	position winPosition;

public:
	baseGameClass() {
		this->winWidth = GetSystemMetrics(SM_CXSCREEN);
		this->winHeight = GetSystemMetrics(SM_CXSCREEN);
		this->winPosition = { 0, 31 }; /// 31-высота плашки окна виндовс -- как получить ее размер???
	}
	~baseGameClass()
	{

	}

	bool initModuls() {

		

		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			success = false;
		}

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}



		gameSettings::win = SDL_CreateWindow("GameLive", this->winPosition.i, this->winPosition.j,
			 this->winWidth, this->winHeight, SDL_WINDOW_SHOWN);

		

		if (gameSettings::win == nullptr) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		gameSettings::surface = SDL_GetWindowSurface(gameSettings::win);
		if (gameSettings::surface == nullptr)
		{
			success = false;
		}
		return success;
	}


};

