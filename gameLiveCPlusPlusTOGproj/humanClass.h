#pragma once

#include"settings.h"
#include"queueClass.h"

class humanClass
{
protected:
	short int hp = 0;
	short int stamina = 0;
	short int satiety = 0;
	position humanPosition;
	queueClass tasksQueue;
	bool work = false;
public:
	humanClass(position pos)
	{
		this->humanPosition.i = pos.i;
		this->humanPosition.j = pos.j;
		this->hp = gameSettings::humanSetting.hp;
		this->stamina = gameSettings::humanSetting.stamina;
		this->satiety = gameSettings::humanSetting.satiety;
	}
	~humanClass() { }
	short int getStamina()
	{
		return stamina;
	}
	
	void setQueue(queueClass queue)
	{
		this->tasksQueue = queue;
	}

	position getPosition()
	{
		return this->humanPosition;
	}

	short int humanTransmit()
	{
		if (tasksQueue.getSize() > 0)
		{
			task task = this->tasksQueue.getFirst();
			//std::cout << task.position.i << " " << task.position.j << std::endl;
			short int deltaX = abs(task.position.j - this->humanPosition.j);
			short int deltaY = abs(task.position.i - this->humanPosition.i);
			if (deltaX != 0 || deltaY != 0)
			{
				if (deltaX > deltaY)
				{
					if (task.position.j > this->humanPosition.j)
					{
						this->humanPosition.j++;
					}
					else
					{
						this->humanPosition.j--;
					}
				}
				else if (task.position.i > this->humanPosition.i)
				{
					this->humanPosition.i++;
				}
				else
				{
					this->humanPosition.i--;
				}
			}
			else
			{
				if (task.workTime == 0)
				{
					this->tasksQueue.getTask();
					if (task.type == taskType::getWood)
					{
						return taskType::getWood;
					}
					else if (task.type == taskType::getStone)
					{
						return taskType::getStone;
					}
					else if (task.type == taskType::buildingFarm)
					{
						return taskType::buildingFarm;
					}
					else if (task.type == taskType::buildingHouse)
					{
						return taskType::buildingHouse;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					this->tasksQueue.reduceTime();
				}
			}
		}
		return 0;
	}
};

