#pragma once

#include"binarySort.h"

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
	short int foodInArea = 0;
	short int stoneInArea = 0;
	short int woodInArea = 0;
	queueClass farmerTasksQueue;
public:
	houseAreaClass(position pos, std::vector<std::vector<cell>> field, houseAreasPoints hap, bool h1, bool h2, bool h3, bool h4 )
	{
		houseHouses[0] = h1;
		houseHouses[1] = h2;
		houseHouses[2] = h3;
		houseHouses[3] = h4;
		this->house = houseClass(pos.i, pos.j);
		findObjects(field, hap);
		if (this->treesInArea.size() != 0)
		{
			quickSort(treesInArea, 0, treesInArea.size() - 1, house.getPosition());
		}
		if (this->rocksInArea.size() != 0)
		{
			quickSort(rocksInArea, 0, rocksInArea.size() - 1, house.getPosition());
		}
		if (this->bushesInArea.size() != 0)
		{
			quickSort(bushesInArea, 0, bushesInArea.size() - 1, house.getPosition());
		}
		this->humans.push_back(new farmerClass(house.getPosition()));
		createFarmerQueue(0);
	}
	~houseAreaClass() 
	{
		this->treesInArea.clear();
		this->rocksInArea.clear();
		this->bushesInArea.clear();
		this->humans.clear();
		this->farms.clear();
	}

	void spawnBuilder()
	{
		this->humans.push_back(new builderClass(house.getPosition()));
	}

	//******************************************************* эти функции работают коректно (проверено)

	void findObjects(std::vector<std::vector<cell>> field, houseAreasPoints hap)
	{
		for (int i = hap.searchStartPos.i; i <= hap.searchEndtPos.i; i++)
		{
			for (int j = hap.searchStartPos.j; j <= hap.searchEndtPos.j; j++)
			{
				if (field[i][j].hasSmth)
				{
					if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::tree)
					{
						treeClass tree = treeClass(field[i][j].position);
						//std::cout << field[i][j].position.i << " " << field[i][j].position.j << std::endl;
						this->treesInArea.push_back(tree);
					}
					else if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::rock)
					{
						rockClass rock = rockClass(field[i][j].position);
						this->rocksInArea.push_back(rock);
					}
				}
			}
		}
		for (int i = hap.houseAreaStartPos.i; i <= hap.houseAreaEndPos.i; i++)
		{
			for (int j = hap.houseAreaStartPos.j; j <= hap.houseAreaEndPos.j; j++)
			{
				if (field[i][j].hasSmth)
				{
					if (field[i][j].objectType == gameSettings::fieldSetting.objectEnum::bushWithBerry)
					{
						bushClass bush = bushClass(field[i][j].position);
						this->bushesInArea.push_back(bush);
					}
				}
			}
		}
	}

	std::vector<humanClass*> getHumans()
	{
		return this->humans;
	}

	void setHumans(std::vector<humanClass*> humans)
	{
		this->humans = humans;
	}

	std::vector<treeClass> getTrees()
	{
		return this->treesInArea;
	}

	std::vector<bushClass> getBushesInArea()
	{
		return this->bushesInArea;
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
		this->foodInArea;
	}

	void sendFood(int sendFood)
	{
		return;
	}

	short int getFarmsCount()
	{
		return this->farms.size();
	}

	short int distance(position point1, position point2)
	{
		return abs(point1.i - point2.i) + abs(point1.j - point2.j);
	}

	void setFarmerQueue()
	{
		this->humans[0]->setQueue(this->farmerTasksQueue);
	}

	//**********************************************************

	void createFarmerQueue(short int humanNumber) // без ферм работает (проверено)
	{
		this->foodInArea = 0;
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
			this->foodInArea += gameSettings::farmSetting.income;
			currentPosition = this->farms[i].getPosition();
			staminaСounter -= (distanceToWorkPlace + workTime);
			distanceFromWorkPlaceToHouse = distance(currentPosition, this->farms[i].getPosition());
		}
		short int numberOfExtrractedBush = 0;
		if (bushesInArea.size() != 0)
		{
			while (this->bushesInArea[numberOfExtrractedBush].getTempResources() == 0)
			{
				numberOfExtrractedBush++;
			}
			distanceToWorkPlace = distance(currentPosition, this->bushesInArea[numberOfExtrractedBush].getPosition());
			workTime = 4;
			distanceFromWorkPlaceToHouse = distance(this->bushesInArea[numberOfExtrractedBush].getPosition(), this->house.getPosition());
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (staminaСounter >= taskExpenses)
			{
				task = { this->bushesInArea[numberOfExtrractedBush].getPosition(), workTime, taskType::getFood };
				tasksQueue.addTask(task);
				this->foodInArea += gameSettings::objectSetting.bushResources;
				staminaСounter -= (distanceToWorkPlace + workTime);
				this->bushesInArea[numberOfExtrractedBush].setTempResources(0);
				currentPosition = this->bushesInArea[numberOfExtrractedBush].getPosition();
				short int numberOfNearestBush = searchNearestObject(this->bushesInArea, numberOfExtrractedBush);
				if (numberOfNearestBush == -1)
				{
					break;
				}
				numberOfExtrractedBush = numberOfNearestBush;
				distanceToWorkPlace = distance(currentPosition, this->bushesInArea[numberOfExtrractedBush].getPosition());
				workTime = 4;
				distanceFromWorkPlaceToHouse = distance(this->bushesInArea[numberOfExtrractedBush].getPosition(), this->house.getPosition());
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			}
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			staminaСounter -= distanceFromWorkPlaceToHouse;
			this->farmerTasksQueue = tasksQueue;

			this->humans[humanNumber]->setQueue(tasksQueue);
		}
	}

	bool createBuilderQueue(short int taskType, short int humanNumber)
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
		short int staminaWork;
		if (taskType == taskType::getWood) //работает (проверено)
		{
			while (staminaСounter > 0)
			{
				short int numberOfExtrractedTree = 0; //номер добываемого дерева
				quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
				while (this->treesInArea[numberOfExtrractedTree].getTempResources() == 0)
				{
					if (this->treesInArea.size() == 0)
					{
						return false;
					}
					else
					{
						this->treesInArea.erase(this->treesInArea.begin() + numberOfExtrractedTree);
					}
				}
				distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[numberOfExtrractedTree].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
				if (staminaWork < 0)
				{
					staminaWork = 0;
				}
				workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfExtrractedTree].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				if (staminaСounter < taskExpenses)
				{
					break;
				}
				while (quantityOfFreeSlots > 0)
				{
					if (staminaСounter >= taskExpenses)
					{
						//добавление задачи бежать к ближайшей скале и добывать её
						task = { this->treesInArea[numberOfExtrractedTree].getPosition(), workTime, taskType };
						tasksQueue.addTask(task);
						this->woodInArea += workTime;
						std::cout << "wood+" << workTime << std::endl;
						quantityOfFreeSlots -= workTime;
						staminaСounter -= distanceToWorkPlace;
						this->treesInArea[numberOfExtrractedTree].setTempResources(this->treesInArea[numberOfExtrractedTree].getTempResources() - workTime);
						staminaСounter -= workTime;
						if (quantityOfFreeSlots > 0)
						{
							short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree); // номер камня, ближайшего к добытому камню
							if (numberOfNearestTree == -1)
							{
								break;
							}
							distanceToWorkPlace = distance(this->treesInArea[numberOfExtrractedTree].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
							numberOfExtrractedTree = numberOfNearestTree;
							distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
							staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
							if (staminaWork < 0)
							{
								staminaWork = 0;
							}
							workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
					}
					else
					{
						break;
					}
				}
				//добавление задачи идти домой
				task = { this->house.getPosition(), 0, 0 };
				tasksQueue.addTask(task);
				staminaСounter -= distanceFromWorkPlaceToHouse;
			}
		}
		else if (taskType == taskType::getStone) //раьотает (проверено)
		{
			while (staminaСounter > 0)
			{
				short int numberOfExtrractedRock = 0; //номер добываемой скалыы
				quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
				while (this->rocksInArea[numberOfExtrractedRock].getTempResources() == 0)
				{
					if (this->rocksInArea.size() == 0)
					{
						return false;
					}
					else
					{
						this->rocksInArea.erase(this->rocksInArea.begin());
					}
				}
				distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedRock].getPosition());
				distanceFromWorkPlaceToHouse = distanceToWorkPlace;
				staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
				if (staminaWork < 0)
				{
					staminaWork = 0;
				}
				workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfExtrractedRock].getTempResources()));
				taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
				if (staminaСounter < taskExpenses)
				{
					break;
				}
				while (quantityOfFreeSlots > 0)
				{
					if (staminaСounter >= taskExpenses)
					{
						//добавление задачи бежать к ближайшей скале и добывать её
						task = { this->rocksInArea[numberOfExtrractedRock].getPosition(), workTime, taskType };
						tasksQueue.addTask(task);
						this->stoneInArea += workTime;
						std::cout << "stone+" << workTime << std::endl;
						quantityOfFreeSlots -= workTime;
						staminaСounter -= distanceToWorkPlace;
						this->rocksInArea[numberOfExtrractedRock].setTempResources(this->rocksInArea[numberOfExtrractedRock].getTempResources() - workTime);
						staminaСounter -= workTime;

						if (quantityOfFreeSlots > 0)
						{
							short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock); // номер камня, ближайшего к добытому камню
							if (numberOfNearestRock == -1)
							{
								break;
							}
							distanceToWorkPlace = distance(this->rocksInArea[numberOfExtrractedRock].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
							numberOfExtrractedRock = numberOfNearestRock;
							distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
							staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
							if (staminaWork < 0)
							{
								staminaWork = 0;
							}
							workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
							taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
						}
					}
					else
					{
						break;
					}
				}
				//добавление задачи идти домой
				task = { this->house.getPosition(), 0, 0 };
				tasksQueue.addTask(task);
				staminaСounter -= distanceFromWorkPlaceToHouse;
			}
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
					if (housePosition.i >= 4 && housePosition.i < 97 && housePosition.j >= 4 && housePosition.j < 97)
					{
						task = { housePosition, gameSettings::houseSetting.workTime, taskType };
						tasksQueue.addTask(task);
						task = { this->house.getPosition(), 0, 0 };
						tasksQueue.addTask(task);
						staminaСounter -= (distanceToWorkPlace * 2 + gameSettings::farmSetting.workTime);
						this->houseHouses[i] = true;
						this->humans[humanNumber]->setQueue(tasksQueue);
						return true;
					}
					this->houseHouses[i] = true;
					return false;
				}
			}
		}
		else if (taskType == taskType::getSomething) //работает (проверено)
		{
			bool rockFlag = false;
			bool treeFlag = false;
			while (staminaСounter > 0)
			{
				short int numberOfExtrractedObject = 0; //номер добываемой скалыы
				quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
				if (this->treesInArea.size() > 0)
				{
					while (this->treesInArea[0].getTempResources() == 0)
					{
						this->treesInArea.erase(this->treesInArea.begin());
						if (this->treesInArea.size() == 0)
						{
							treeFlag = true;
							break;
						}
					}
				}
				else
				{
					treeFlag = true;
				}
				if (this->rocksInArea.size() > 0)
				{
					while (this->rocksInArea[0].getTempResources() == 0)
					{
						this->rocksInArea.erase(this->rocksInArea.begin());
						if (this->rocksInArea.size() == 0)
						{
							rockFlag = true;
							break;
						}
					}
				}
				else
				{
					rockFlag = true;
				}
				if (rockFlag == true || treeFlag == true)
				{
					return false;
				}
				short int material;
				if (distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedObject].getPosition()) < distance(this->house.getPosition(), this->treesInArea[numberOfExtrractedObject].getPosition()))
				{
					distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[numberOfExtrractedObject].getPosition());
					distanceFromWorkPlaceToHouse = distanceToWorkPlace;
					staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
					if (staminaWork < 0)
					{
						staminaWork = 0;
					}
					workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
					taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					material = material::stone;
				}
				else
				{
					distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[numberOfExtrractedObject].getPosition());
					distanceFromWorkPlaceToHouse = distanceToWorkPlace;
					staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
					if (staminaWork < 0)
					{
						staminaWork = 0;
					}
					workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
					taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					material = material::wood;
				}
				if (staminaСounter < taskExpenses)
				{
					break;
				}
				while (quantityOfFreeSlots > 0)
				{
					if (staminaСounter >= taskExpenses)
					{
						//добавление задачи бежать к ближайшей скале и добывать её
						if (material == material::stone)
						{
							task = { this->rocksInArea[numberOfExtrractedObject].getPosition(), workTime, taskType::getStone };
							this->stoneInArea += workTime;
							std::cout << "stone+" << workTime << std::endl;
							this->rocksInArea[numberOfExtrractedObject].setTempResources(this->rocksInArea[numberOfExtrractedObject].getTempResources() - workTime);
						}
						else
						{
							task = { this->treesInArea[numberOfExtrractedObject].getPosition(), workTime, taskType::getWood };
							this->woodInArea += workTime;
							std::cout << "wood+" << workTime << std::endl;
							this->treesInArea[numberOfExtrractedObject].setTempResources(this->treesInArea[numberOfExtrractedObject].getTempResources() - workTime);
						}
						tasksQueue.addTask(task);
						quantityOfFreeSlots -= workTime;
						staminaСounter -= (distanceToWorkPlace + workTime);
						if (quantityOfFreeSlots > 0)
						{
							short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedObject); // номер камня, ближайшего к добытому объекту
							short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedObject); // номер дерева, ближайшего к добытому объекту
							short int distanceToRockPlace = 0;
							short int distanceToTreePlace = 0;
							if (numberOfNearestRock == -1 && numberOfNearestTree == -1)
							{
								break;
							}
							else if (numberOfNearestTree == -1)
							{
								distanceToTreePlace = gameSettings::humanSetting.stamina + 1;
							}
							else if (numberOfNearestRock == -1)
							{
								distanceToRockPlace = gameSettings::humanSetting.stamina + 1;
							}
							else
							{
								if (material == material::stone)
								{
									distanceToRockPlace = distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
									distanceToTreePlace = distance(this->rocksInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
								}
								else
								{
									distanceToRockPlace = distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
									distanceToTreePlace = distance(this->treesInArea[numberOfExtrractedObject].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
								}
							}
							if (material == material::stone)
							{
								if (distanceToRockPlace < distanceToTreePlace)
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
								if (distanceToRockPlace < distanceToTreePlace)
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
								std::cout << "numberOfNearestRock: " << numberOfNearestRock << std::endl;
								distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
								staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
								if (staminaWork < 0)
								{
									staminaWork = 0;
								}
								workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
								taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
							}
							else
							{
								numberOfExtrractedObject = numberOfNearestTree;
								std::cout << "numberOfNearestTree: " << numberOfNearestTree << std::endl;
								distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
								staminaWork = staminaСounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse;
								if (staminaWork < 0)
								{
									staminaWork = 0;
								}
								workTime = (short int)std::fmin(staminaWork, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
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
				task = { this->house.getPosition(), 0, 0 };
				tasksQueue.addTask(task);
				staminaСounter -= distanceFromWorkPlaceToHouse;
			}
		}
		this->humans[humanNumber]->setQueue(tasksQueue);
		return false;
	}
	
};

