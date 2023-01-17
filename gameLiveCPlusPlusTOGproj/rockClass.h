#pragma once
#include "objectClass.h"
class rockClass :
    public objectClass
{
public:
    rockClass(position pos) :objectClass(pos)
    {
        resources = gameSettings::objectSetting.rockResources;
        tempResources = gameSettings::objectSetting.rockResources;
    }
    void blit() {}
};

