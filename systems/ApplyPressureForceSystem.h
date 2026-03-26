#ifndef APPLY_PRESSURE_FORCE_SYSTEM_H
#define APPLY_PRESSURE_FORCE_SYSTEM_H
#include "../core/System.h"
#include <glm/glm.hpp>
#include "../core/Coordinator.h"
#include "../components/Transform3D.h"
#include "../settings/Settings.h"
#include "../components/Mass.h"
#include "../components/Force.h"
#include "../components/Pressure.h"
#include "../components/Density.h"
#include <math.h>
extern Coordinator coordinator;

class ApplyPressureForceSystem : public System {
public:
    void update(float);

private:

};

#endif
