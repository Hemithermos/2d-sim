#include "ClearForcesSystem.h"
#include "../core/Coordinator.h"
#include "../components/Force.h"


extern Coordinator coordinator;

void ClearForcesSystem::update()
{

    for(Entity e : listOfEntities)
    {
        coordinator.getComponent<Force>(e).force = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}