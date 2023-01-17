#pragma once

#include "settings.h"

class queueClass
{
private:
	std::vector<task> arrayQueue;
	int size = 0;
public:
	~queueClass()
	{
	}
	int getSize()
	{
		return this->size;
	}
	void addTask(task a)
	{
		this->arrayQueue.push_back(a);
		this->size++;
	}
	bool Is_empty()
	{
		return this->size != 0;
	}
	void getTask()
	{
		this->arrayQueue.erase(this->arrayQueue.begin());
		this->size--;
	}
	task getFirst()
	{
		if (this->arrayQueue.size() > 0)
		{
			return this->arrayQueue[0];
		}
	}
	void reduceTime()
	{
		this->arrayQueue[0].workTime--;
	}
};


