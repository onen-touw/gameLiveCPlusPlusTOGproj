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
		short int stamina�ounter = this->humans[humanNumber]->getStamina();
		queueClass<task> tasksQueue;
		task task;
		// ���-�� ��������� ������ � ��������� ���������
		short int quantityOfFreeSlots = gameSettings::builderSetting.inventorySize - ((builderClass*)this->humans[humanNumber])->getResourcesCount();
		short int distanceToWorkPlace; // ���������� �� �������� �����
		short int distanceFromWorkPlaceToHouse; // ���������� �� �������� ����� �� ����
		short int workTime; //����� ������� ����� ��������� �� ������
		short int taskExpenses; // ���-�� ������� ����������� ��� ���� ����� �������� ������ ������ ���� ������ � ��������� �����
		if (taskType == taskType::getWood)
		{
			short int numberOfExtrractedTree = 0; //����� ����������� ������
			distanceToWorkPlace = distance(this->house.getPosition(), this->treesInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(stamina�ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (stamina�ounter >= taskExpenses)
				{
					//���������� ������ ������ � ��������� ����� � �������� �
					task = { this->treesInArea[numberOfExtrractedTree].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->treesInArea[numberOfExtrractedTree].setTempResources(this->treesInArea[numberOfExtrractedTree].getTempResources() - workTime);
					if (this->treesInArea[numberOfExtrractedTree].getTempResources() == 0)
					{
						this->treesInArea.erase(this->treesInArea.begin(), this->treesInArea.begin());
					}
					stamina�ounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestTree = searchNearestObject(this->treesInArea, numberOfExtrractedTree); // ����� �����, ���������� � �������� �����
						numberOfExtrractedTree = numberOfNearestTree;
						distanceToWorkPlace = distance(this->treesInArea[0].getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->treesInArea[numberOfNearestTree].getPosition());
						workTime = (short int)std::fmin(stamina�ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->treesInArea[numberOfNearestTree].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//���������� ������ ���� �����
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			stamina�ounter -= distanceFromWorkPlaceToHouse;
		}
		if (taskType == taskType::getStone)
		{
			short int numberOfExtrractedRock = 0; //����� ���������� ������
			distanceToWorkPlace = distance(this->house.getPosition(), this->rocksInArea[0].getPosition());
			distanceFromWorkPlaceToHouse = distanceToWorkPlace;
			workTime = (short int)std::fmin(stamina�ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[0].getTempResources()));
			taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
			while (quantityOfFreeSlots > 0)
			{
				if (stamina�ounter >= taskExpenses)
				{
					//���������� ������ ������ � ��������� ����� � �������� �
					task = { this->rocksInArea[numberOfExtrractedRock].getPosition(), workTime };
					tasksQueue.addTask(task);
					quantityOfFreeSlots -= workTime;
					this->rocksInArea[numberOfExtrractedRock].setTempResources(this->rocksInArea[numberOfExtrractedRock].getTempResources() - workTime);
					if (this->rocksInArea[numberOfExtrractedRock].getTempResources() == 0)
					{
						this->rocksInArea.erase(this->rocksInArea.begin(), this->rocksInArea.begin());
					}
					stamina�ounter -= (distanceToWorkPlace + workTime);
					if (quantityOfFreeSlots > 0)
					{
						short int numberOfNearestRock = searchNearestObject(this->rocksInArea, numberOfExtrractedRock); // ����� �����, ���������� � �������� �����
						distanceToWorkPlace = distance(this->rocksInArea[0].getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						distanceFromWorkPlaceToHouse = distance(this->house.getPosition(), this->rocksInArea[numberOfNearestRock].getPosition());
						workTime = (short int)std::fmin(stamina�ounter - distanceToWorkPlace - distanceFromWorkPlaceToHouse, std::fmin(quantityOfFreeSlots, this->rocksInArea[numberOfNearestRock].getTempResources()));
						taskExpenses = distanceToWorkPlace + distanceFromWorkPlaceToHouse + workTime;
					}
				}
				else
				{
					break;
				}
			}
			//���������� ������ ���� �����
			task = { this->house.getPosition(), 0 };
			tasksQueue.addTask(task);
			stamina�ounter -= distanceFromWorkPlaceToHouse;
		}

	}
};

