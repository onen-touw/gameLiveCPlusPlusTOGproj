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
	std::vector<humanClass*> humans;
	std::vector<farmClass> farms;
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
		short int quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)humans[humanNumber])->getResourcesCount();
		short int distanceToWorkPlace;
		short int workTime;
		short int taskExpenses;
		if (taskType == taskType::getWood)
		{
			distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[treesInArea.size() - 1].getPosition());
			workTime = std::fmin(staminaСounter - distanceToWorkPlace * 2, std::fmin(quantityOfFreeSlots, this->treesInArea[treesInArea.size() - 1].getResources()));
			taskExpenses = distanceToWorkPlace * 2 + workTime;
			if (staminaСounter >= taskExpenses)
			{
				//добавление задачи бежать к ближайшему дереву и добывать его
				task = { this->treesInArea[treesInArea.size() - 1].getPosition(), workTime };
				tasksQueue.addTask(task);
				staminaСounter -= (distanceToWorkPlace + workTime);
				if(quantityOfFreeSlots > 0) 
				{
					//если в инвенторе есть место ищем ближайшее дерево и если хватает энергии идем его добывать
				} 
				//добавление задачи идти домой
				task = { house.getPosition(), 0 };
				tasksQueue.addTask(task);
				staminaСounter -= workTime;
			}
		}
		if (taskType == taskType::getStone)
		{
			distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[rocksInArea.size() - 1].getPosition());
			workTime = std::fmin(staminaСounter - distanceToWorkPlace * 2, std::fmin(quantityOfFreeSlots, this->rocksInArea[treesInArea.size() - 1].getResources()));
			taskExpenses = distanceToWorkPlace * 2 + workTime;
			if (staminaСounter >= taskExpenses)
			{
				//добавление задачи бежать к ближайшей скале и добывать её
				task = { rocksInArea[rocksInArea.size() - 1].getPosition(), workTime };
				tasksQueue.addTask(task);
				staminaСounter -= (distanceToWorkPlace + workTime);
				if (quantityOfFreeSlots > 0)
				{
					//если в инвенторе есть место ищем ближайшую скалу и если хватает энергии идем её добывать
				} 
				//добавление задачи идти домой
				task = { house.getPosition(), 0 };
				tasksQueue.addTask(task);
				staminaСounter -= workTime;
			}
		}
	}
};

