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

struct sizes
{
	short int width = 0;
	short int height = 0;
};

struct houseSettings
{
	sizes size = { 2, 2 };
};

struct farmSettings
{
	sizes size = { 3, 3 };
};



namespace gameSettings {
	extern humanSettings humanSetting;

}