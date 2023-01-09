#pragma once
#include "humanClass.h"
class builderClass :
    public humanClass
{
private:
    short int* inventory;
    short int resourcesCount;
public:
    builderClass(short int i, short int j):humanClass(i, j)
    {
        this->inventory = new short int[gameSettings::builderSetting.inventorySize] { 0, 0, 0, 0 };
        this->resourcesCount = 0;
    }
    ~builderClass()
    {
        delete[] inventory;
    }
    void addToInventory(short int resource)
    {
        if (this->resourcesCount != gameSettings::builderSetting.inventorySize)
        {
            for (int i = 0; i < gameSettings::builderSetting.inventorySize; i++)
            {
                if (this->inventory[i] == 0)
                {
                    this->inventory[i] = resource;
                    this->resourcesCount++;
                    break;
                }
            }
        }
    }
};

