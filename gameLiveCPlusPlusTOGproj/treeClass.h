#pragma once
#include "objectClass.h"
class treeClass :
    public objectClass
{
private:
    
public:
    treeClass(position pos):objectClass(pos)
    {
        resources = gameSettings::objectSetting.treeResources;
    }
    void blit() { }
};

