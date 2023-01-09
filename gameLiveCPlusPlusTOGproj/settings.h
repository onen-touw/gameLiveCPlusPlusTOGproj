#pragma once

#include <iostream>
#include <vector>
#include <string>

struct position
{
	short int i = 0;
	short int j = 0;
};

struct humanSettings
{
	short int hp = 10;
	short int stamina = 160;
	short int satiety = 6;
};




namespace gameSettings {
	extern humanSettings humanSetting;

}