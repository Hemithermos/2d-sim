#include "IntegratePositionSystem.h"

#include "../core/Coordinator.h"
#include "../components/Velocity.h"
#include "../components/Transform3D.h"
#include "../components/PreviousPosition.h"
extern Coordinator coordinator;


void IntegratePositionSystem::update(float dt)
{
    for(Entity e : listOfEntities) {
        auto& pos = coordinator.getComponent<Transform3D>(e);
        auto& vel = coordinator.getComponent<Velocity>(e);
        auto& prevpos = coordinator.getComponent<PreviousPosition>(e);

        prevpos.previousPosition = pos.position;
        pos.position += vel.velocity * dt;
    }
}