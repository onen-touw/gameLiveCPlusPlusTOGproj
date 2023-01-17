#pragma once

#include"settings.h"

template <class Data> 
short int searchNearestObject(std::vector<Data> objectsInArea, short int objectNumber)
{
	short int numberOfNearestObject = -1;
	short int minimalDistance = gameSettings::humanSetting.stamina + 1;
	for (int i = 0; i < objectsInArea.size(); i++)
	{
		if (objectsInArea[i].getTempResources() != 0 && i != objectNumber)
		{
			short int distance = abs((objectsInArea[objectNumber].getPosition()).i - (objectsInArea[i].getPosition()).i) + abs((objectsInArea[objectNumber].getPosition()).j - (objectsInArea[i].getPosition()).j);
			if (distance < minimalDistance)
			{
				minimalDistance = distance;
				numberOfNearestObject = i;
			}
		}
	}
	return numberOfNearestObject;
}