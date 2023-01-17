#pragma once
#include "objectClass.h"
class bushClass :
    public objectClass
{
public:
    bushClass(position pos) :objectClass(pos)
    {
        resources = gameSettings::objectSetting.bushResources;
        tempResources = gameSettings::objectSetting.bushResources;
    }
    void blit() {}
};

