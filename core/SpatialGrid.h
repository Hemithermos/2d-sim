#ifndef CORE_SPATIAL_GRID_H
#define CORE_SPATIAL_GRID_H
#include "vector"
#include "unordered_map"
#include "core/Entity.h"
#include "glm/glm.hpp"
class SpatialGrid {

public:
    SpatialGrid(float, float, float);
    void clear();
    void insert(Entity, const glm::vec3);



private:


};


#endif