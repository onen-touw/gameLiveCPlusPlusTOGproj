#pragma once

#include"settings.h"

class humanClass
{
private :
	int hp = gameSettings::humanSetting.hp;
public:
	int getHp() { return this->hp; }
	void setHp(int hp) {
		this->hp = hp
	}
};

