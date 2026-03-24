#ifndef PARTICLE_COLLISIONS_SYSTEM_H
#define PARTICLE_COLLISIONS_SYSTEMS_H

#include "../core/System.h"
constexpr float RESTITUTION = 1.01f;
class ParticleCollisionSystem : public System {
public:
    void update(float);


};


#endif