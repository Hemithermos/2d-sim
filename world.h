// world.h
#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>
#include "core/Coordinator.h"

extern Coordinator coordinator;

class World {
    public:

    World() {};
    void spawnParticle(glm::vec3 pos, glm::vec3 vel, float m, float radius,
                      glm::vec3 color = {1.0f, 0.0f, 0.0f},
                      glm::vec3 f = {0.0f, 0.0f, 0.0f});

    void init();

    private:
};

#endif
