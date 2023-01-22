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



	bool play = true;

	short btnCount = 0;
	short btnSpraiteListX = 0; 
	short btnSize = 0;
public:
	headerClass() {
		this->loadImages(gameSettings::headerImagesPathVector);
		this->logOut();
		this->winWidth = gameSettings::fieldSetting.minCountCellInWin.width* gameSettings::winObjSize.cellSize;
		this->btnSize = gameSettings::winObjSize.menuHeader;
		this->btnCount = gameSettings::headerSetting.btns::btnsTOTAL;
		this->btnSpraiteListX = this->winWidth - this->btnSize * this->btnCount;
	}

	void blitHeader() {
		SDL_Rect mr = { 0,0, this->winWidth,
			gameSettings::winObjSize.menuHeader };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::bg], NULL, gameSettings::surface, &mr);
		this->counter(0, 0, 0, 0);
		this->btnsBlit();
		this->blitXClock(gameSettings::settlmentSetting.startTimeRation);
	}

	/// счетчики 
	void counter(int wood, int food, int stone, int people) {
		SDL_Rect mr = {0,this->padingTop, this->padingLeft * 4 + this->resurseImgSize * 4 + this->numberWidth * 12 + this->numberWidth * 5, this->numberHeight };
		SDL_Rect cr = {};
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::bg],
			NULL, gameSettings::surface, &mr);
		

		std::string sCount = std::to_string(wood);

		mr = { this->padingLeft , this->padingTop, this->resurseImgSize,this->resurseImgSize };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::wood],
			NULL, gameSettings::surface, &mr);


		for (int i = 0; i < sCount.size(); i++)
		{
			mr = { this->padingLeft+ this->resurseImgSize + this->numberWidth*i, this->padingTop, this->numberWidth,this->numberHeight,  };
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

	void blitXClock(short timeRation) {
		std::string temp = std::to_string(timeRation);

		SDL_Rect mr = {this->winWidth/2, this->padingTop, this->btnSize*2,this->numberHeight };
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::clockX], NULL, gameSettings::surface, &mr);
		SDL_Rect cr;
		for (int i = 0; i < temp.size(); i++)
		{
			cr = { this->crNumberWidth * (temp[i] - '0'),
				0 , this->crNumberWidth, this->crNumberHeight };
			mr = { this->winWidth / 2 + this->btnSize * 2 + this->numberWidth * i, this->padingTop, this->numberWidth,this->numberHeight };
			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::numbers],
				&cr, gameSettings::surface, &mr);
			SDL_UpdateWindowSurface(gameSettings::win);
		}
	}

	void btnsBlit() {
		SDL_Rect mr = { this->btnSpraiteListX, 0, this->btnSize* this->btnCount, this->btnSize};
		SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::btnSpriteList], NULL, gameSettings::surface, &mr);
		SDL_UpdateWindowSurface(gameSettings::win);
	}

	~headerClass()
	{
		this->imageVector.clear();
	}
	
	short getBtnSpriteListX() { return this->btnSpraiteListX; }

	/// при учете высоты кнопок равной высоте хедера
	short btnParse(int cursoreX) {
		for (int i = 0; i < this->btnCount; i++)
		{
			if (cursoreX >= i * this->btnSize + this->btnSpraiteListX && cursoreX < (i +1)* this->btnSize + this->btnSpraiteListX)
			{
				return i;
			}
		}
		return -1;
	}
	
	void toggleForPlayBtn(bool flag) {
		SDL_Rect mr = { this->btnSpraiteListX, 0, this->btnSize, this->btnSize};
		if (flag)
		{
			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::pauseBtn], NULL, gameSettings::surface,&mr);
		}
		else
		{
			SDL_BlitScaled(this->imageVector[gameSettings::headerSetting.headerImgs::playBtn], NULL, gameSettings::surface, &mr);
		}
		SDL_UpdateWindowSurface(gameSettings::win);
	}



};

