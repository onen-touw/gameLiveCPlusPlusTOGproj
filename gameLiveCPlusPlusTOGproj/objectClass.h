#pragma once

#include"settings.h"

class objectClass
{
protected:
	position objectPosition;
	short int resources = 0;
public:
	objectClass(short int i, short int j)
	{
		this->objectPosition.i = i;
		this->objectPosition.j = j;
	}
	~objectClass() { }

	bool decreaseResourse() {
		if (--this->resources == 0) { return false; }
		return true;
	}
	
	short int getResources()
	{
		return resources;
	}

	position getPosition()
	{
		return objectPosition;
	}

	void blit() {}
};

