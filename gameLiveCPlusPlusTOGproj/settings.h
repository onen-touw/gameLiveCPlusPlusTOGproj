#pragma once

#include <iostream>
#include <vector>
#include <string>

struct humanSettings
{
	short int hp = 10;
	short int stamina = 30;
	short int satiety = 6;
};

struct position
{
	short int i = 0;
	short int j = 0;
};


namespace gameSettings {
	extern humanSettings humanSetting;

}