#include "IntegratePressureSystem.h"

void IntegratePressureSystem::update(float)
{
    for(auto e : listOfEntities) {
        auto& density = coordinator.getComponent<Density>(e).density;
        auto& pressure = coordinator.getComponent<Pressure>(e).pressure;

        pressure = std::max(PRESSURE_MULTIPLIER * (density - TARGET_DENSITY), 0.0f);
    }
}