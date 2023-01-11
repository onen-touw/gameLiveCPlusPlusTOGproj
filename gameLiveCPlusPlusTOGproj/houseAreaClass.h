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
#include"searchNearestObject.h"

class houseAreaClass
{
private:
	std::vector<treeClass> treesInArea;
	std::vector<rockClass> rocksInArea;
	std::vector<bushClass> bushesInArea;
	std::vector<humanClass*> humans;
	std::vector<farmClass> farms;
	bool houseFarms[4] = { false, false, false, false };
	bool houseHouses[4] = { false, false, false, false };
	houseClass house = houseClass(0, 0);
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

	

	queueClass<task> createBuilderQueue(short int taskType, short int humanNumber)
	{
		short int staminaСounter = this->humans[humanNumber]->getStamina();
		queueClass<task> tasksQueue;
		task task;
		// кол-во свободных слотов в инвенторе строителя
		short int quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
		short int distanceToWorkPlace; // расстояние до рабочего места
		short int distanceFromWorkPlaceToHouse; // расстояние от рабочего места до дома
		short int workTime; //время которое нужно затратить на работу
		short int taskExpenses; // кол-во энергии необходимое для того чтобы добежать добыть хотябы один ресурс и вернуться домой
		if (taskType == taskType::getWood)
		{
			short int numberOfExtrractedTree = 0; //номер добываемого дерева
			distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (staminaСounter >= taskExpenses)
				{
					//добавление задачи бежать к ближайшей скале и добывать её
					task = { this->treesInArea[numberOfExtrractedTree].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->treesInArea[numberOfExtrractedTree].setTempResources(this->treesInArea[numberOfExtrractedTree].getTempResources() - workTime);
					if (this->treesInArea[numberOfExtrractedTree].getTempResources() == 0)
					{
						this->treesInArea.erase(this->treesInArea.begin(), this->treesInArea.begin());
					}
					staminaСounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree); // номер камня, ближайшего к добытому камню
						numberOfExtrractedTree = numberOfNearestTree;
						distanceToWorkPlace = distance(this->treesInArea[0].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//добавление задачи идти домой
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			staminaСounter -= distanceFromWorkPlaceToHouse;
		}
		if (taskType == taskType::getStone)
		{
			short int numberOfExtrractedRock = 0; //номер добываемой скалыы
			distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (staminaСounter >= taskExpenses)
				{
					//добавление задачи бежать к ближайшей скале и добывать её
					task = { this->rocksInArea[numberOfExtrractedRock].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->rocksInArea[numberOfExtrractedRock].setTempResources(this->rocksInArea[numberOfExtrractedRock].getTempResources() - workTime);
					if (this->rocksInArea[numberOfExtrractedRock].getTempResources() == 0)
					{
						this->rocksInArea.erase(this->rocksInArea.begin(), this->rocksInArea.begin());
					}
					staminaСounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock); // номер камня, ближайшего к добытому камню
						distanceToWorkPlace = distance(this->rocksInArea[0].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//добавление задачи идти домой
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			staminaСounter -= distanceFromWorkPlaceToHouse;
		}
		if (taskType == taskType::buildingFarm)
		{
			
		}
	}
};

