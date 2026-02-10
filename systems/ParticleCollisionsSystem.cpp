#include "ParticleCollisionsSystem.h"
#include "../components/Velocity.h"
#include "../components/Transform3D.h"
#include "../components/Spherical.h"
#include "../components/Mass.h"
#include "../core/Coordinator.h"

extern Coordinator coordinator;
void resolveCollision(Entity, Entity);

void ParticleCollisionSystem::update(float dt)
{
    for(auto itA = listOfEntities.begin() ; itA != listOfEntities.end(); ++itA) {
        Entity a = *itA;
        auto itB = itA;
        ++itB;
        for(; itB != listOfEntities.end() ; ++itB) {
            Entity b = *itB;
            resolveCollision(a,b);

        }
    }
}

void resolveCollision(Entity a, Entity b) {

    auto& posA = coordinator.getComponent<Transform3D>(a).position;
    auto& posB = coordinator.getComponent<Transform3D>(b).position;

    auto& velA = coordinator.getComponent<Velocity>(a).velocity;
    auto& velB = coordinator.getComponent<Velocity>(b).velocity;

    auto& radA = coordinator.getComponent<Spherical>(a).radius;
    auto& radB = coordinator.getComponent<Spherical>(b).radius;

    auto& massA = coordinator.getComponent<Mass>(a).mass;
    auto& massB = coordinator.getComponent<Mass>(b).mass;

    glm::vec3 delta = posB - posA;
    float dist2 = glm::dot(delta, delta);
    float minDist = radA + radB;

    if (dist2 >= minDist * minDist || dist2 == 0.0f)
        return;

    float dist = std::sqrt(dist2);
    glm::vec3 normal = delta / dist;

    // --- masses
    float invMassA = 1.0f / massA;
    float invMassB = 1.0f / massB;
    float invMassSum = invMassA + invMassB;

    // --- position correction
    float penetration = minDist - dist;
    glm::vec3 correction = normal * penetration / invMassSum;
    posA -= correction * invMassA;
    posB += correction * invMassB;

    // --- velocity correction
    glm::vec3 relVel = velB - velA;
    float sepVel = glm::dot(relVel, normal);

    if (sepVel > 0.0f)
        sepVel = 0.0f;

    float restitution = 1.0f;
    float impulse =
        -(1.0f + restitution) * sepVel / invMassSum;

    glm::vec3 impulseVec = impulse * normal;
    velA -= impulseVec * invMassA;
    velB += impulseVec * invMassB;


}