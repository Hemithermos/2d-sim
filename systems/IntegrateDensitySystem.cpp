#include "IntegrateDensitySystem.h"



void IntegrateDensitySystem::update(float)
{
    const float h = SMOOTHING_RADIUS;
    const float h2 = h * h;

    const float poly6 = 315.0f / (64.0f * M_PI * pow(h, 9));

    for (auto entity_i : listOfEntities)
    {
        auto& transform_i = coordinator.getComponent<Transform3D>(entity_i);
        auto& mass_i      = coordinator.getComponent<Mass>(entity_i);
        auto& density_i   = coordinator.getComponent<Density>(entity_i);

        float rho = 0.0f;

        for (auto entity_j : listOfEntities)
        {
            auto& transform_j = coordinator.getComponent<Transform3D>(entity_j);
            auto& mass_j      = coordinator.getComponent<Mass>(entity_j);

            glm::vec3 rij = transform_i.position - transform_j.position;
            float r2 = glm::dot(rij, rij);

            if (r2 < h2)
            {
                float term = h2 - r2;
                rho += mass_j.mass * poly6 * term * term * term;
            }
        }

        density_i.density = rho;
    }
}
