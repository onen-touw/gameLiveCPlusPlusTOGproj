#pragma once

#include"settings.h"

class objectClass
{
protected:
	position objectPosition;
	short int resources = 0;
	short int tempResources = 0;

public:
	objectClass(position pos)
	{
		this->objectPosition.i = pos.i;
		this->objectPosition.j = pos.j;
	}
	~objectClass() { }

	bool decreaseResourse() {
		if (--this->resources == 0) { return false; }
		return true;
	}
	
	short int getTempResources()
	{
		return this->tempResources;
	}

	void setTempResources(short int tempResources)
	{
		this->tempResources = tempResources;
	}

	position getPosition()
	{
		return this->objectPosition;
	}

	void blit() {}
};

