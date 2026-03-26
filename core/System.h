#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include <vector>
#include "Entity.h"

// every system should inherit that class
class System
{
public:
    std::vector<Entity> listOfEntities;
};

#endif