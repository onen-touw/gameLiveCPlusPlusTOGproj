#pragma once

#include"imageClass.h"

class headerClass : public imageClass
{

private:
	short numberHeight = 40;
	short numberWidth = 30;
	short resurseImgSize = 40;

	short crNumberWidth = 171;
	short crNumberHeight = 300;

	short padingTop = 20;
	short padingLeft = 20;
	
	short winWidth = 0;

	short btnSize = 0;

	bool play = true;

public:
	headerClass() {
		this->loadImages(gameSettings::headerImagesPathVector);
		this->logOut();
		this->winWidth = gameSettings::fieldSetting.minCountCellInWin.width* gameSettings::winObjSize.cellSize;
		this->btnSize = gameSettings::winObjSize.menuHeader;
	}

	void blitHeader() {
		SDL_Rect mr = { 0,0, this->winWidth,
			gameSettings::winObjSize.menuHeader };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::bg], NULL, gameSettings::surface, &mr);
		this->counter(0, 0, 0, 0);
		this->btnsBlit();
	}

	/// счетчики 
	void counter(int wood, int food, int stone, int people) {

		std::string sCount = std::to_string(wood);

		SDL_Rect mr = { this->padingLeft , this->padingTop, this->resurseImgSize,this->resurseImgSize };
		SDL_Rect cr = {};
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::wood],
			NULL, gameSettings::surface, &mr);


		for (int i = 0; i < sCount.size(); i++)
		{
			mr = { this->padingLeft+ this->resurseImgSize + this->numberWidth*i, this->padingTop, this->numberWidth,this->numberHeight };
			cr = {this->crNumberWidth *(sCount[i] - '0'),
				0 , this->crNumberWidth, this->crNumberHeight };

			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::numbers],
				&cr, gameSettings::surface, &mr);
		}

		sCount = std::to_string(stone);

		mr = { this->padingLeft*2 + this->resurseImgSize + this->numberWidth * 4, this->padingTop, this->resurseImgSize,this->resurseImgSize };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::stone],
			NULL, gameSettings::surface, &mr);

		for (int i = 0; i < sCount.size(); i++)
		{
			mr = { this->padingLeft*2+ this->resurseImgSize*2 + this->numberWidth*4 + this->numberWidth * i, this->padingTop, this->numberWidth,this->numberHeight };
			cr = { this->crNumberWidth * (sCount[i] - '0'),
				0 , this->crNumberWidth, this->crNumberHeight };

			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::numbers],
				&cr, gameSettings::surface, &mr);
		}
		sCount = std::to_string(food);

		mr = { this->padingLeft*3 + this->resurseImgSize*2 + this->numberWidth * 8, this->padingTop, this->resurseImgSize,this->resurseImgSize };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::food],
			NULL, gameSettings::surface, &mr);

		for (int i = 0; i < sCount.size(); i++)
		{
			mr = { this->padingLeft*3 + this->resurseImgSize * 3 + this->numberWidth * 8 + this->numberWidth * i, this->padingTop, this->numberWidth,this->numberHeight };
			cr = { this->crNumberWidth * (sCount[i] - '0'),
				0 , this->crNumberWidth, this->crNumberHeight };

			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::numbers],
				&cr, gameSettings::surface, &mr);
		}

		sCount = std::to_string(people);

		mr = { this->padingLeft * 4 + this->resurseImgSize * 3 + this->numberWidth * 12, this->padingTop, this->resurseImgSize,this->resurseImgSize };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::people],
			NULL, gameSettings::surface, &mr);

		for (int i = 0; i < sCount.size(); i++)
		{
			mr = { this->padingLeft * 4 + this->resurseImgSize * 4 + this->numberWidth * 12 + this->numberWidth * i, this->padingTop, this->numberWidth,this->numberHeight };
			cr = { this->crNumberWidth * (sCount[i] - '0'),
				0 , this->crNumberWidth, this->crNumberHeight };

			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::numbers],
				&cr, gameSettings::surface, &mr);
		}
		SDL_UpdateWindowSurface(gameSettings::win);
	}

	void btnsBlit() {
		SDL_Rect mr = { this->winWidth - this->btnSize * 6, 0, this->btnSize*6, this->btnSize};
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::btnSpriteList], NULL, gameSettings::surface, &mr);
		SDL_UpdateWindowSurface(gameSettings::win);
	}

	~headerClass()
	{
		this->imageVector.clear();
	}


	

};

