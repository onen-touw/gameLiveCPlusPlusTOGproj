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
	queueClass<task> tasksQueue;
	bool work = false;
public:
	humanClass(short int i, short int j)
	{
		this->humanPosition.i = i;
		this->humanPosition.j = j;
		this->hp = gameSettings::humanSetting.hp;
		this->stamina = gameSettings::humanSetting.stamina;
		this->satiety = gameSettings::humanSetting.satiety;
	}
	~humanClass() { }
	short int getStamina()
	{
		return stamina;
	}
};

