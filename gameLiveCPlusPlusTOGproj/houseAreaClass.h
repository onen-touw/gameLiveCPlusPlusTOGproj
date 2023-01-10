#pragma once

#include"settings.h"

#include"builderClass.h"
#include"farmerClass.h"

#include"bushClass.h"
#include"rockClass.h"
#include"treeClass.h"

#include"farmClass.h"
#include"houseClass.h"

#include"queueClass.h"

class houseAreaClass
{
private:
	std::vector<treeClass> treesInArea;
	std::vector<rockClass> rocksInArea;
	std::vector<bushClass> bushesInArea;
	std::vector<humanClass> humans;
	std::vector<farmClass> farms;
	houseClass house = houseClass(0, 0);
	houseAreaSettings Coords;
public:
	houseAreaClass(short int i, short int j, int* pole)
	{
		this->house = houseClass(i, j);
		

	}
	~houseAreaClass() { }

	short int distance(position point1, position point2)
	{
		return abs(point1.i - point2.i) + abs(point1.j - point2.j);
	}

	queueClass<position> createBuilderQueue(short int taskType, short int humanNumber)
	{
		short int staminacounter = humans[humanNumber].getStamina();
		if (taskType == 1)
		{
			position task = this->treesInArea[treesInArea.size() - 1].getPosition();
			if (staminacounter >= distance(this->house.getPosition(), task))
			{

			}
		}
	}
};

