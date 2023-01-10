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
		this->winPosition = { 0, 31 }; /// 31-������ ������ ���� ������� -- ��� �������� �� ������???
	}
	~baseGameClass()
	{

	}

	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "problem::SDL_Init\n" << SDL_GetError << "\n";
			success = false;
			return success;
		}

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
			return success;
		}

		gameSettings::win = SDL_CreateWindow("GameLive", this->winPosition.i, this->winPosition.j,
			 this->winWidth, this->winHeight, SDL_WINDOW_SHOWN);

		if (gameSettings::win == nullptr) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
			return success;
		}
		gameSettings::surface = SDL_GetWindowSurface(gameSettings::win);
		if (gameSettings::surface == nullptr)
		{
			std::cout << "problem::surface\n";
			success = false;
			return success;
		}
		return success;
	}


};

