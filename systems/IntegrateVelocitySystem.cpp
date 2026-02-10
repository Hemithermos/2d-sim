#include "IntegrateVelocitySystem.h"

#include "../core/Coordinator.h"
#include "../components/Force.h"
#include "../components/Velocity.h"
#include "../components/Mass.h"
extern Coordinator coordinator;


void IntegrateVelocitySystem::update(float dt)
{
    for(Entity e : listOfEntities) {
        auto& force = coordinator.getComponent<Force>(e);
        auto& velocity = coordinator.getComponent<Velocity>(e);
        auto& mass = coordinator.getComponent<Mass>(e);
        
        assert(mass.mass > 0.0f);
        velocity.velocity += (force.force / mass.mass) * dt ;
    }
}