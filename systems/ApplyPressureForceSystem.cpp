#include "ApplyPressureForceSystem.h"

void ApplyPressureForceSystem::update(float)
{
    const float h = SMOOTHING_RADIUS;

    const float spikyGrad = -45.0f / (M_PI * pow(h, 6));

    for (auto entity_i : listOfEntities)
    {
        auto& transform_i = coordinator.getComponent<Transform3D>(entity_i);
        auto& density_i   = coordinator.getComponent<Density>(entity_i);
        auto& pressure_i  = coordinator.getComponent<Pressure>(entity_i);
        auto& force_i     = coordinator.getComponent<Force>(entity_i);

        glm::vec3 f_pressure(0.0f);

        for (auto entity_j : listOfEntities)
        {
            if (entity_i == entity_j) continue;

            auto& transform_j = coordinator.getComponent<Transform3D>(entity_j);
            auto& density_j   = coordinator.getComponent<Density>(entity_j);
            auto& pressure_j  = coordinator.getComponent<Pressure>(entity_j);
            auto& mass_j      = coordinator.getComponent<Mass>(entity_j);

            glm::vec3 rij = transform_i.position - transform_j.position;
            float r = glm::length(rij);

            if (r < h && r > 0.0001f)
            {
                glm::vec3 dir = rij / r;

                float coeff = spikyGrad * (h - r) * (h - r);

                glm::vec3 gradW = coeff * dir;

                float pressureTerm =
                    (pressure_i.pressure / (density_i.density * density_i.density)) +
                    (pressure_j.pressure / (density_j.density * density_j.density));

                f_pressure += -mass_j.mass * pressureTerm * gradW;
            }
        }

        force_i.force += f_pressure;
    }
}
