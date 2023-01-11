#pragma once

#include "settings.h"

template <class Data> class queueClass
{
private:
	std::vector<Data> arrayQueue;
	int size = 0;
public:
	int getSize()
	{
		return this->size;
	}
	void addTask(Data a)
	{
		this->arrayQueue.push_back(a);
		this->size++;
	}
	void print()
	{
		for (int i = 0; i < this->size; i++)
		{
			std::cout << this->arrayQueue[i] << " ";
		}
		std::cout << std::endl;
	}
	bool Is_empty()
	{
		return this->size != 0;
	}
	Data getTask()
	{
		Data a = this->arrayQueue[0];
		this->arrayQueue.erase(this->arrayQueue.begin(), this->arrayQueue.begin() + 1);
		this->size--;
		return a;
	}
};


