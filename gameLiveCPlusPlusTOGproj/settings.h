#pragma once

#include <iostream>
#include <vector>
#include <string>

struct position
{
	short int i = 0;
	short int j = 0;
};

struct task
{
	short int i = 0;
	short int j = 0;
	short int workTime = 0;
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
	short int income = 10;
};

enum material
{
	wood = 1,
	stone
};

struct builderSettings
{
	short int inventorySize = 4;
};

struct houseAreaSettings
{
	short int i1 = 0;
	short int j1 = 0;
	short int i2 = 0;
	short int j2 = 0;
	short int i3 = 0;
	short int j3 = 0;
	short int i4 = 0;
	short int j4 = 0;
};


namespace gameSettings {
	extern humanSettings humanSetting;
	extern farmSettings farmSetting;
	extern builderSettings builderSetting;
}