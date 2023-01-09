#pragma once

#include"settings.h"
#include"queueClass.h"

class humanClass
{
protected:
	short int hp = 0;
	short int stamina = 0;
	short int satiety = 0;
	position humanPosition;
	queueClass<position> taskQueue;
	bool work = false;
	short int homeNumber = 0;
public:
	humanClass(short int i, short int j, short int homeNumber)
	{
		this->humanPosition.i = i;
		this->humanPosition.j = j;
		this->homeNumber = homeNumber;
		this->hp = gameSettings::humanSetting.hp;
		this->stamina = gameSettings::humanSetting.stamina;
		this->satiety = gameSettings::humanSetting.satiety;
	}
	~humanClass() { }
};

