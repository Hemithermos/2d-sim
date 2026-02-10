#ifndef APPLY_EXTERNAL_FORCES_SYSTEM_H
#define APPLY_EXTERNAL_FORCES_SYSTEM_H

#include "../core/System.h"
#include "../components/Force.h"
#include "../components/Mass.h"

constexpr glm::vec3 GRAVITY = { 0.0f, -9.81f, 0.0f };


class ApplyExternalForcesSystem : public System
{
public:
    void update(float dt);


private:


};

#endif