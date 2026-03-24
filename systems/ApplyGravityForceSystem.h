#ifndef APPLY_GRAVITY_FORCE_SYSTEM_H
#define APPLY_GRAVITY_FORCE_SYSTEM_H

#include "../core/System.h"
#include "../components/Force.h"
#include "../components/Mass.h"
#include "../settings/Settings.h"


class ApplyGravityForceSystem : public System
{
public:
    void update(float dt);


private:


};

#endif