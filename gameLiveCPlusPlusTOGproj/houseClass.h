#pragma once

#include"settings.h"

class houseClass
{
protected:
	position housePosition;
	sizes houseSize;
public:
	houseClass(short int i, short int j)
	{
		this->housePosition.i = i;
		this->housePosition.j = j;
	}
	~houseClass() { }
	void blit(){}
};

