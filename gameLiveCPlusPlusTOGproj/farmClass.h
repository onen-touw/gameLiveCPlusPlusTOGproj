#pragma once

#include"settings.h"

class farmClass
{
protected:
	position farmPosition;
	sizes farmSize;
	short int income = 0;
public:
	farmClass(short int i, short int j)
	{
		this->farmPosition.i = i;
		this->farmPosition.j = j;
		this->income = gameSettings::farmSetting.income;
	}
	~farmClass() { }
	void blit() {}
};

