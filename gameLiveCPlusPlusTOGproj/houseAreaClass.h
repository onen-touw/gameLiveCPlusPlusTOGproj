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
		short int stamina—ounter = this->humans[humanNumber]->getStamina();
		queueClass<task> tasksQueue;
		task task;
		// ÍÓÎ-‚Ó Ò‚Ó·Ó‰Ì˚ı ÒÎÓÚÓ‚ ‚ ËÌ‚ÂÌÚÓÂ ÒÚÓËÚÂÎˇ
		short int quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
		short int distanceToWorkPlace; // ‡ÒÒÚÓˇÌËÂ ‰Ó ‡·Ó˜Â„Ó ÏÂÒÚ‡
		short int distanceFromWorkPlaceToHouse; // ‡ÒÒÚÓˇÌËÂ ÓÚ ‡·Ó˜Â„Ó ÏÂÒÚ‡ ‰Ó ‰ÓÏ‡
		short int workTime; //‚ÂÏˇ ÍÓÚÓÓÂ ÌÛÊÌÓ Á‡Ú‡ÚËÚ¸ Ì‡ ‡·ÓÚÛ
		short int taskExpenses; // ÍÓÎ-‚Ó ˝ÌÂ„ËË ÌÂÓ·ıÓ‰ËÏÓÂ ‰Îˇ ÚÓ„Ó ˜ÚÓ·˚ ‰Ó·ÂÊ‡Ú¸ ‰Ó·˚Ú¸ ıÓÚˇ·˚ Ó‰ËÌ ÂÒÛÒ Ë ‚ÂÌÛÚ¸Òˇ ‰ÓÏÓÈ
		if (taskType == taskType::getWood)
		{
			short int numberOfExtrractedTree = 0; //ÌÓÏÂ ‰Ó·˚‚‡ÂÏÓ„Ó ‰ÂÂ‚‡
			distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (stamina—ounter >= taskExpenses)
				{
					//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë ·ÂÊ‡Ú¸ Í ·ÎËÊ‡È¯ÂÈ ÒÍ‡ÎÂ Ë ‰Ó·˚‚‡Ú¸ Â∏
					task = { this->treesInArea[numberOfExtrractedTree].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->treesInArea[numberOfExtrractedTree].setTempResources(this->treesInArea[numberOfExtrractedTree].getTempResources() - workTime);
					if (this->treesInArea[numberOfExtrractedTree].getTempResources() == 0)
					{
						this->treesInArea.erase(this->treesInArea.begin(), this->treesInArea.begin());
					}
					stamina—ounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree); // ÌÓÏÂ Í‡ÏÌˇ, ·ÎËÊ‡È¯Â„Ó Í ‰Ó·˚ÚÓÏÛ Í‡ÏÌ˛
						numberOfExtrractedTree = numberOfNearestTree;
						distanceToWorkPlace = distance(this->treesInArea[0].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë Ë‰ÚË ‰ÓÏÓÈ
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			stamina—ounter -= distanceFromWorkPlaceToHouse;
		}
		if (taskType == taskType::getStone)
		{
			short int numberOfExtrractedRock = 0; //ÌÓÏÂ ‰Ó·˚‚‡ÂÏÓÈ ÒÍ‡Î˚˚
			distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (stamina—ounter >= taskExpenses)
				{
					//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë ·ÂÊ‡Ú¸ Í ·ÎËÊ‡È¯ÂÈ ÒÍ‡ÎÂ Ë ‰Ó·˚‚‡Ú¸ Â∏
					task = { this->rocksInArea[numberOfExtrractedRock].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->rocksInArea[numberOfExtrractedRock].setTempResources(this->rocksInArea[numberOfExtrractedRock].getTempResources() - workTime);
					if (this->rocksInArea[numberOfExtrractedRock].getTempResources() == 0)
					{
						this->rocksInArea.erase(this->rocksInArea.begin(), this->rocksInArea.begin());
					}
					stamina—ounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock); // ÌÓÏÂ Í‡ÏÌˇ, ·ÎËÊ‡È¯Â„Ó Í ‰Ó·˚ÚÓÏÛ Í‡ÏÌ˛
						numberOfExtrractedRock = numberOfNearestRock;
						distanceToWorkPlace = distance(this->rocksInArea[0].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë Ë‰ÚË ‰ÓÏÓÈ
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			stamina—ounter -= distanceFromWorkPlaceToHouse;
		}
		if (taskType == taskType::buildingFarm)
		{
			for (int i = 0; i < 4; i++)
			{
				position farmPosition;
				if (i == 1)
				{
					farmPosition = { short int(this->house.getPosition().i - 2), this->house.getPosition().j };
					distanceToWorkPlace = 2;
				}
				else if (i == 2)
				{
					farmPosition = { this->house.getPosition().i, short int(this->house.getPosition().j + 3) };
					distanceToWorkPlace = 3;
				}
				else if (i == 3)
				{
					farmPosition = { short int(this->house.getPosition().i + 1), short int(this->house.getPosition().j - 2) };
					distanceToWorkPlace = 3;
				}
				else
				{
					farmPosition = { short int(this->house.getPosition().i + 3), short int(this->house.getPosition().j + 1) };
					distanceToWorkPlace = 4;
				}
				if (this->houseFarms[i] == false)
				{
					if (distance(this->house.getPosition(), this->treesInArea[0].getPosition()) > 6)
					{
						if (distance(this->house.getPosition(), this->rocksInArea[0].getPosition()) > 6)
						{
							for (int j = 0; j < this->bushesInArea.size(); i++)
							{
								if (distance(this->bushesInArea[j].getPosition(), farmPosition) < 2)
								{
									this->bushesInArea.erase(this->bushesInArea.begin() + j, this->bushesInArea.begin() + j + 1);
								}
							}
							task = { farmPosition, gameSettings::farmSetting.workTime };
							tasksQueue.addTask(task);
							task = { this->house.getPosition(), 0 };
							tasksQueue.addTask(task);
							stamina—ounter -= (distanceToWorkPlace * 2 + gameSettings::farmSetting.workTime );
							this->houseFarms[i] = true;
							farmClass farm = farmClass(farmPosition.i, farmPosition.j);
							this->farms.push_back(farm);
							break;
						}
					}
				}
			}
		}
		if (taskType == taskType::buildingHouse)
		{
			for (int i = 0; i < 4; i++)
			{
				position housePosition;
				distanceToWorkPlace = 20;
				if (i == 1)
				{
					housePosition = { short int(this->house.getPosition().i - 20), this->house.getPosition().j };
				}
				else if (i == 2)
				{
					housePosition = { this->house.getPosition().i, short int(this->house.getPosition().j + 20) };
				}
				else if (i == 3)
				{
					housePosition = { short int(this->house.getPosition().i + 20), this->house.getPosition().j };
				}
				else
				{
					housePosition = { this->house.getPosition().i, short int(this->house.getPosition().j - 20) };
				}
				if (this->houseHouses[i] == false)
				{
					
					task = { housePosition, gameSettings::farmSetting.workTime };
					tasksQueue.addTask(task);
					task = { this->house.getPosition(), 0 };
					tasksQueue.addTask(task);
					stamina—ounter -= (distanceToWorkPlace * 2 + gameSettings::farmSetting.workTime);
					this->houseFarms[i] = true;
					farmClass farm = farmClass(housePosition.i, housePosition.j);
					this->farms.push_back(farm);
					break;		
				}
			}
		}
		if (taskType == taskType::getSomething)
		{
			short int numberOfExtrractedObject = 0; //ÌÓÏÂ ‰Ó·˚‚‡ÂÏÓÈ ÒÍ‡Î˚˚
			short int material;
			if (distance(this->house.getPosition(), this->rocksInArea[0].getPosition()) < distance(this->house.getPosition(), this->treesInArea[0].getPosition()))
			{
				distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[0].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				material = material::stone;
			}
			else
			{
				distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[0].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				material = material::wood;
			}
			while (quantityOfFreeSlots > 0)
			{
				if (stamina—ounter >= taskExpenses)
				{
					//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë ·ÂÊ‡Ú¸ Í ·ÎËÊ‡È¯ÂÈ ÒÍ‡ÎÂ Ë ‰Ó·˚‚‡Ú¸ Â∏
					if (material == material::stone)
					{
						task = { this->rocksInArea[numberOfExtrractedObject].getPosition(), workTime };
						this->rocksInArea[numberOfExtrractedObject].setTempResources(this->rocksInArea[numberOfExtrractedObject].getTempResources() - workTime);
						if (this->rocksInArea[numberOfExtrractedObject].getTempResources() == 0)
						{
							this->rocksInArea.erase(this->rocksInArea.begin(), this->rocksInArea.begin());
						}
					}
					else
					{
						task = { this->treesInArea[numberOfExtrractedObject].getPosition(), workTime };
						this->treesInArea[numberOfExtrractedObject].setTempResources(this->treesInArea[numberOfExtrractedObject].getTempResources() - workTime);
						if (this->treesInArea[numberOfExtrractedObject].getTempResources() == 0)
						{
							this->treesInArea.erase(this->treesInArea.begin(), this->treesInArea.begin());
						}
					}
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					stamina—ounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedObject); // ÌÓÏÂ Í‡ÏÌˇ, ·ÎËÊ‡È¯Â„Ó Í ‰Ó·˚ÚÓÏÛ Ó·˙ÂÍÚÛ
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedObject); // ÌÓÏÂ ‰ÂÂ‚‡, ·ÎËÊ‡È¯Â„Ó Í ‰Ó·˚ÚÓÏÛ Ó·˙ÂÍÚÛ
						if (material == material::stone)
						{
							if (distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition()) < distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition()))
							{
								distanceToWorkPlace = distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
								material = material::stone;
							}
							else
							{
								distanceToWorkPlace = distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
								material = material::wood;
							}
						}
						else
						{
							if (distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition()) < distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition()))
							{
								distanceToWorkPlace = distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
								material = material::stone;
							}
							else
							{
								distanceToWorkPlace = distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
								material = material::wood;
							}
						}
						if (material == material::stone)
						{
							numberOfExtrractedObject = numberOfNearestRock;
							distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
							workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
						else
						{
							numberOfExtrractedObject = numberOfNearestTree;
							distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
							workTime = (short int)std::fmin(stamina—ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
					}
				}
				else
				{
					break;
				}
			}
			//‰Ó·‡‚ÎÂÌËÂ Á‡‰‡˜Ë Ë‰ÚË ‰ÓÏÓÈ
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			stamina—ounter -= distanceFromWorkPlaceToHouse;
		}
	}
};

