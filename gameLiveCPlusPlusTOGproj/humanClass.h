#pragma once

#include"settings.h"

class humanClass
{
private :
	int hp = 0;
	int stamina = 0;
	int satiety = 0;
	position humanPosition;

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

	int getHp() { return this->hp; }
};

