#ifndef INTEGRATE_PRESSURE_SYSTEM_H
#define INTEGRATE_PRESSURE_SYSTEM_H

#include "../core/System.h"
#include "../core/Coordinator.h"
#include "../components/Mass.h"
#include "../components/Transform3D.h"
#include "../components/Density.h"
#include "../settings/Settings.h"
#include "../components/Pressure.h"

extern Coordinator coordinator;
class IntegratePressureSystem : public System {
public:
    void update(float);

private:
};


#endif