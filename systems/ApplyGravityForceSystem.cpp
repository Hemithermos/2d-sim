#include "ApplyGravityForceSystem.h"
#include "../core/Coordinator.h"


extern Coordinator coordinator;

void ApplyGravityForceSystem::update(float dt)
{
    for(Entity e : listOfEntities)
    {
        auto& force = coordinator.getComponent<Force>(e);
        auto& mass = coordinator.getComponent<Mass>(e);
    
        force.force += mass.mass * GRAVITY;
    }


}