#pragma once

#include <iostream>
#include <vector>
#include <string>
 
enum material
{
	wood = 1,
	stone
};
enum taskType
{
	getWood = 1,
	getStone,
	buildingFarm,
	buildingHouse
};

struct position
{
	short int i = 0;
	short int j = 0;
};

struct task
{
	position position = { 0,0 };
	short int workTime = 0;
};

struct humanSettings
{
	short int hp = 10;
	short int stamina = 160; // TODO: связать время дня и кол-во стамины
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

struct builderSettings
{
	short int inventorySize = 4;
};

namespace gameSettings {
	extern humanSettings humanSetting;
	extern farmSettings farmSetting;
	extern builderSettings builderSetting;
}