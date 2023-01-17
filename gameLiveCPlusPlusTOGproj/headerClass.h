#pragma once

#include"settings.h"
//#include"oneImgUpload.h"

class headerClass
{

private:

	
	

public:
	headerClass() {
		/*this->headerImgs.resize(gameSettings::headerSetting.menuImgs::menuImgsTOTAL);
		this->headerImgs[gameSettings::headerSetting.menuImgs::numbers] = loagOneImg("./images/headerImgs/numbers.png");
		this->headerImgs[gameSettings::headerSetting.menuImgs::bg] = loagOneImg("./images/headerImgs/bgTemp.png");*/
		//this->menuImgs[gameSettings::menuSetting.menuImgs::] = loagOneImg("/");
	}

	void blitHeader() {
		SDL_Rect mr = { 0,0, gameSettings::fieldSetting.minCountCellInWin.width * gameSettings::winObjSize.cellSize,
			gameSettings::winObjSize.menuHeader };
		//SDL_BlitScaled(this->headerImgs[gameSettings::headerSetting.menuImgs::bg], NULL, gameSettings::surface, &mr);


	}

	void counter(int count, int i) {

	}

	~headerClass()
	{

	}

};

