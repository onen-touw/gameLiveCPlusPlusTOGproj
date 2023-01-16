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

	position getPosition()
	{
		return this->humanPosition;
	}

	bool humanTransmit()
	{
		task task = this->tasksQueue.getFirst();
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
				return true;
			}
			else
			{
				this->tasksQueue.reduceTime();
			}
		}
		return false;
	}
};

