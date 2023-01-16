#pragma once

#include<algorithm>

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
	std::vector<objectClass> objects;
	std::vector<humanClass*> humans;
	std::vector<farmClass> farms;
	std::vector<houseClass> nextHouses; // соседние дома
	bool houseFarms[4] = { false, false, false, false };
	bool houseHouses[4] = { false, false, false, false };
	houseClass house = houseClass(0, 0);
	short int foodInArea = 0;
	short int stoneInArea = 0;
	short int woodInArea = 0;
public:
	houseAreaClass(position pos, std::vector<std::vector<cell>> field )
	{
		this->house = houseClass(pos.i, pos.j);
		findObjects(field);
		//sort(treesInArea.begin(), treesInArea.end(), [](auto& a, auto& b) {return distance(a.getPosition(), house.getPosition()) < distance(b.getPosition(), house.getPosition())});
		//sort(rocksInArea.begin(), rocksInArea.end(), [](auto& a, auto& b) {return distance(a.getPosition(), house.getPosition()) < distance(b.getPosition(), house.getPosition())});
		//sort(bushesInArea.begin(), bushesInArea.end(), [](auto& a, auto& b) {return distance(a.getPosition(), house.getPosition()) < distance(b.getPosition(), house.getPosition())});
		this->humans.push_back(new farmerClass(house.getPosition()));
		createFarmerQueue(0);
	}
	~houseAreaClass() { }

	void findObjects(std::vector<std::vector<cell>> field)
	{
		for (int i = 0; i < field.size(); i++)
		{
			for (int j = 0; j < field[i].size(); j++)
			{
				if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::tree)
				{
					treeClass tree = treeClass(field[i][j].position);
					this->treesInArea.push_back(tree);
				}
				else if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::rock)
				{
					rockClass rock = rockClass(field[i][j].position);
					this->rocksInArea.push_back(rock);
				}
				else if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::bushWithBerry)
				{
					bushClass bush = bushClass(field[i][j].position);
					this->bushesInArea.push_back(bush);
				}
			}
		}
	}

	std::vector<humanClass*> getHumans()
	{
		return this->humans;
	}

	short int getWood()
	{
		return this->woodInArea;
	}

	void claimWood()
	{
		this->woodInArea = 0;
	}

	short int getStone()
	{
		return this->stoneInArea;
	}

	void claimStone()
	{
		this->stoneInArea = 0;
	}

	short int getFreeFood()
	{
		return this->foodInArea - this->humans.size() * gameSettings::humanSetting.deilyRation;
	}

	void claimFood(int sentFood)
	{
		this->foodInArea -= sentFood;
	}

	void sendFood(int sendFood)
	{
		this->foodInArea += sendFood;
	}

	short int getFarmsCount()
	{
		return this->farms.size();
	}

	short int distance(position point1, position point2)
	{
		return abs(point1.i - point2.i) + abs(point1.j - point2.j);
	}

	void createFarmerQueue(short int humanNumber)
	{
		short int staminaСounter = humans[0]->getStamina();
		short int distanceToWorkPlace; // расстояние до рабочего места
		short int distanceFromWorkPlaceToHouse; // расстояние от рабочего места до дома
		short int workTime; //время которое нужно затратить на работу
		short int taskExpenses; // кол-во энергии необходимое для того чтобы добежать добыть хотябы один ресурс и вернуться домой
		position currentPosition = this->house.getPosition();
		queueClass tasksQueue;
		task task;
		for (int i = 0; i < this->farms.size(); i++)
		{
			distanceToWorkPlace = distance(currentPosition, this->farms[i].getPosition());
			workTime = gameSettings::farmSetting.income;
			task = { this->farms[i].getPosition(), gameSettings::farmSetting.income };
			tasksQueue.addTask(task);
			currentPosition = this->farms[i].getPosition();
			staminaСounter -= (distanceToWorkPlace + workTime);
			distanceFromWorkPlaceToHouse = distance(currentPosition, this->farms[i].getPosition());
		}
		short int numberOfExtrractedBush = 0;
		while (this->bushesInArea[numberOfExtrractedBush].getTempResources() != 0)
		{
			numberOfExtrractedBush++;
		}
		distanceToWorkPlace = distance(currentPosition, this->bushesInArea[numberOfExtrractedBush].getPosition());
		workTime = 1;
		distanceFromWorkPlaceToHouse = distance(this->bushesInArea[numberOfExtrractedBush].getPosition(), this->house.getPosition());
		taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
		while (staminaСounter >= taskExpenses)
		{
			task = { this->bushesInArea[numberOfExtrractedBush].getPosition(), workTime };
			tasksQueue.addTask(task);
			staminaСounter -= (distanceToWorkPlace+workTime);
			this->bushesInArea[numberOfExtrractedBush].setTempResources(0);
			currentPosition = this->bushesInArea[numberOfExtrractedBush].getPosition();
			short int numberOfNearestBush = searchNearestObject(this->bushesInArea, numberOfExtrractedBush);
			numberOfExtrractedBush = numberOfNearestBush;
			distanceToWorkPlace = distance(currentPosition, this->bushesInArea[numberOfExtrractedBush].getPosition());
			workTime = 1;
			distanceFromWorkPlaceToHouse = distance(this->bushesInArea[numberOfExtrractedBush].getPosition(), this->house.getPosition());
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
		}
		task = { this->house.getPosition(), 0 };
		tasksQueue.addTask(task);
		staminaСounter -= distanceFromWorkPlaceToHouse;
	}

	void createBuilderQueue(short int taskType, short int humanNumber)
	{
		short int staminaСounter = gameSettings::humanSetting.stamina;
		queueClass tasksQueue;
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
			while (this->treesInArea[numberOfExtrractedTree].getTempResources() != 0)
			{
				this->treesInArea.erase(this->treesInArea.begin() + numberOfExtrractedTree);
			}
			distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfExtrractedTree].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (staminaСounter >= taskExpenses)
				{
					//добавление задачи бежать к ближайшей скале и добывать её
					task = { this->treesInArea[numberOfExtrractedTree].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					staminaСounter -= distanceToWorkPlace;
					this->treesInArea[numberOfExtrractedTree].setTempResources(this->treesInArea[numberOfExtrractedTree].getTempResources() - workTime);
					if (this->treesInArea[numberOfExtrractedTree].getTempResources() == 0)
					{
						this->treesInArea.erase(this->treesInArea.begin() + numberOfExtrractedTree);
					}
					staminaСounter -= workTime;
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree); // номер камня, ближайшего к добытому камню
						while (this->treesInArea[numberOfNearestTree].getTempResources() != 0)
						{
							this->treesInArea.erase(this->treesInArea.begin() + numberOfNearestTree);
							numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree);
						}
						distanceToWorkPlace = distance(this->treesInArea[numberOfExtrractedTree].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						numberOfExtrractedTree = numberOfNearestTree;
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
		else if (taskType == taskType::getStone)
		{
			short int numberOfExtrractedRock = 0; //номер добываемой скалыы
			while (this->rocksInArea[numberOfExtrractedRock].getTempResources() != 0)
			{
				this->rocksInArea.erase(this->rocksInArea.begin());
			}
			distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedRock].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfExtrractedRock].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (staminaСounter >= taskExpenses)
				{
					//добавление задачи бежать к ближайшей скале и добывать её
					task = { this->rocksInArea[numberOfExtrractedRock].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					staminaСounter -= distanceToWorkPlace;
					this->rocksInArea[numberOfExtrractedRock].setTempResources(this->rocksInArea[numberOfExtrractedRock].getTempResources() - workTime);
					if (this->rocksInArea[numberOfExtrractedRock].getTempResources() == 0)
					{
						this->rocksInArea.erase(this->rocksInArea.begin() + numberOfExtrractedRock);
					}
					staminaСounter -= workTime;
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock); // номер камня, ближайшего к добытому камню
						while (this->rocksInArea[numberOfNearestRock].getTempResources() != 0)
						{
							this->rocksInArea.erase(this->rocksInArea.begin() + numberOfNearestRock);
							numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock);
						}
						distanceToWorkPlace = distance(this->rocksInArea[numberOfExtrractedRock].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						numberOfExtrractedRock = numberOfNearestRock;
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
		else if (taskType == taskType::buildingFarm)
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
				if (distance(this->house.getPosition(), this->rocksInArea[0].getPosition()) > 6)
				{
					if (distance(this->house.getPosition(), this->treesInArea[0].getPosition()) > 6)
					{
						if (this->houseFarms[i] == false)
						{
							task = { farmPosition, gameSettings::farmSetting.workTime };
							tasksQueue.addTask(task);
							task = { this->house.getPosition(), 0 };
							tasksQueue.addTask(task);
							staminaСounter -= (distanceToWorkPlace * 2 + gameSettings::farmSetting.workTime);
							this->houseFarms[i] = true;
							for (int j = 0; j < this->bushesInArea.size(); j++)
							{
								if (distance(this->bushesInArea[j].getPosition(), farmPosition) < 2)
								{
									this->bushesInArea.erase(this->bushesInArea.begin() + j);
									j--;
								}
							}
							farmClass farm = farmClass(farmPosition.i, farmPosition.j);
							this->farms.push_back(farm);
							break;
						}
					}
				}
			}
		}
		else if (taskType == taskType::buildingHouse)
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
					task = { housePosition, gameSettings::houseSetting.workTime };
					tasksQueue.addTask(task);
					task = { this->house.getPosition(), 0 };
					tasksQueue.addTask(task);
					staminaСounter -= (distanceToWorkPlace * 2 + gameSettings::farmSetting.workTime);
					this->houseFarms[i] = true;
					houseClass nextHouse = houseClass(housePosition.i, housePosition.j);
					this->nextHouses.push_back(nextHouse);
					break;		
				}
			}
		}
		else if (taskType == taskType::getSomething)
		{
			short int numberOfExtrractedObject = 0; //номер добываемой скалыы
			while (this->treesInArea[0].getTempResources() != 0)
			{
				this->treesInArea.erase(this->treesInArea.begin());
			}
			while (this->rocksInArea[0].getTempResources() != 0)
			{
				this->rocksInArea.erase(this->rocksInArea.begin());
			}
			short int material;
			if (distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedObject].getPosition()) < distance(this->house.getPosition(), this->treesInArea[numberOfExtrractedObject].getPosition()))
			{
				distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedObject].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				material = material::stone;
			}
			else
			{
				distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[numberOfExtrractedObject].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				material = material::wood;
			}
			while (quantityOfFreeSlots > 0)
			{
				if (staminaСounter >= taskExpenses)
				{
					//добавление задачи бежать к ближайшей скале и добывать её
					if (material == material::stone)
					{
						task = { this->rocksInArea[numberOfExtrractedObject].getPosition(), workTime };
						this->rocksInArea[numberOfExtrractedObject].setTempResources(this->rocksInArea[numberOfExtrractedObject].getTempResources() - workTime);
						if (this->rocksInArea[numberOfExtrractedObject].getTempResources() == 0)
						{
							this->rocksInArea.erase(this->rocksInArea.begin() + numberOfExtrractedObject);
						}
					}
					else
					{
						task = { this->treesInArea[numberOfExtrractedObject].getPosition(), workTime };
						this->treesInArea[numberOfExtrractedObject].setTempResources(this->treesInArea[numberOfExtrractedObject].getTempResources() - workTime);
						if (this->treesInArea[numberOfExtrractedObject].getTempResources() == 0)
						{
							this->treesInArea.erase(this->treesInArea.begin() + numberOfExtrractedObject);
						}
					}
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					staminaСounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedObject); // номер камня, ближайшего к добытому объекту
						while (this->rocksInArea[numberOfNearestRock].getTempResources() != 0)
						{
							this->rocksInArea.erase(this->rocksInArea.begin() + numberOfNearestRock);
							numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedObject);
						}
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedObject); // номер дерева, ближайшего к добытому объекту
						while (this->treesInArea[numberOfNearestTree].getTempResources() != 0)
						{
							this->treesInArea.erase(this->treesInArea.begin() + numberOfNearestTree);
							numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedObject);
						}
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
							workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
						else
						{
							numberOfExtrractedObject = numberOfNearestTree;
							distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
							workTime = (short int)std::fmin(staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
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
	}
};

