#ifndef INTEGRATE_DENSITY_SYSTEM_H
#define INTEGRATE_DENSITY_SYSTEM_H

#include "../core/System.h"
#include "../core/Coordinator.h"
#include "../components/Mass.h"
#include "../components/Transform3D.h"
#include "../components/Density.h"
#include "../settings/Settings.h"

extern Coordinator coordinator;
class IntegrateDensitySystem : public System {
public:
    void update(float);

private:
};


#endif