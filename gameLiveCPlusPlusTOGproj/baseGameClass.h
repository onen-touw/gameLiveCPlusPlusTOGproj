#pragma once

#include"settings.h"
#include <windows.h>

class baseGameClass
{
private:

	position winPosition;
	sizes winSize;

public:
	baseGameClass() {
		
		this->calculateWinParametrs();
		this->winPosition = { 0, gameSettings::winObjSize.winTopBorder }; /// 31-высота плашки окна виндовс -- как получить ее размер???
	}
	~baseGameClass(){}

	void calculateWinParametrs() {
		gameSettings::fieldSetting.minCountCellInWin.height = int((GetSystemMetrics(SM_CYSCREEN) - 100 - 31 - gameSettings::winObjSize.menuHeader) / gameSettings::winObjSize.cellSize);
		gameSettings::fieldSetting.minCountCellInWin.width = int(GetSystemMetrics(SM_CXSCREEN) / gameSettings::winObjSize.cellSize);
		
		this->winSize.width = gameSettings::fieldSetting.minCountCellInWin.width * gameSettings::winObjSize.cellSize;

		this->winSize.height = gameSettings::fieldSetting.minCountCellInWin.height * gameSettings::winObjSize.cellSize + gameSettings::winObjSize.menuHeader;

		std::cout << gameSettings::fieldSetting.minCountCellInWin.height << "x" <<
			gameSettings::fieldSetting.minCountCellInWin.width << "\n" <<
			this->winSize.height << "x" <<
			this->winSize.width << "\n";
	}

	sizes getWinSizes() { return this->winSize; }
	

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
			 this->winSize.width, this->winSize.height, SDL_WINDOW_SHOWN);

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

	//short getWinWidth() { return this->winSize.width; }
};

