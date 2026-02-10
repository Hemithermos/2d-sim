#include "RenderSystem.h"
#include "../components/RenderParticle.h"
#include "../core/Coordinator.h"
#include "../components/Transform3D.h"
#include "../components/PreviousPosition.h"
#include "../components/Spherical.h"
extern Coordinator coordinator;


static glm::vec3 lerp(const glm::vec3& a, const glm::vec3& b, float t) {
    return a * (1.0f - t) + b * t;
} 


void RenderSystem::render(Renderer& renderer, float alpha)
{
    renderer.drawBackground();
    for(Entity e : listOfEntities) {
        const auto& pos  = coordinator.getComponent<Transform3D>(e);
        const auto& prev = coordinator.getComponent<PreviousPosition>(e);
        const auto& rend = coordinator.getComponent<RenderParticle>(e);
        const auto& rad = coordinator.getComponent<Spherical>(e);
        glm::vec3 drawPos = lerp(prev.previousPosition, pos.position, alpha);

        renderer.drawCircle(drawPos, rad.radius, rend.color);
    }

}