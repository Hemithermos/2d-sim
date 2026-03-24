#ifndef APPLY_EXTERNAL_FORCES_SYSTEM_H
#define APPLY_EXTERNAL_FORCES_SYSTEM_H

#include "../core/System.h"
#include "../components/Force.h"
#include "../components/Mass.h"
#include "../settings/Settings.h"


class ApplyExternalForcesSystem : public System
{
public:
    void update(float dt);


private:


};

#endif