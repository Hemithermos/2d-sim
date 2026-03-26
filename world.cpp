// world.cpp
#include "world.h"
#include "components/Transform3D.h"
#include "components/Velocity.h"
#include "components/Force.h"
#include "components/Mass.h"
#include "components/PreviousPosition.h"
#include "components/RenderParticle.h"
#include "components/Spherical.h"
#include "core/Entity.h"
#include <random>
#include "settings/Settings.h"
#include "components/Density.h"
#include "components/Pressure.h"


void World::spawnParticle(glm::vec3 pos, glm::vec3 vel, float m, float radius,
                    glm::vec3 color, glm::vec3 f) {
    Entity particle = coordinator.createEntity();

    coordinator.addComponent(particle, Transform3D{pos});
    coordinator.addComponent(particle, Velocity{vel});
    coordinator.addComponent(particle, Mass{m});
    coordinator.addComponent(particle, Force{f});
    coordinator.addComponent(particle, PreviousPosition{pos});
    coordinator.addComponent(particle, RenderParticle{glm::vec4(color, 1.0f)});
    coordinator.addComponent(particle, Spherical{radius});
    coordinator.addComponent(particle, Density{});
    coordinator.addComponent(particle, Pressure{});
}

void World::init() {

    for(float xi = LEFT_WALL ; xi <= RIGHT_WALL; xi+=(RIGHT_WALL - LEFT_WALL)/NUM_PARTICLE_SQR_ROOT) {
        for(float yi = Y_FLOOR ; yi <= Y_CEILING; yi += (Y_CEILING - Y_FLOOR)/NUM_PARTICLE_SQR_ROOT) {
            spawnParticle({xi, yi, 0.0f}, //position
                {0.0f,0.0f, 0.0f}, //speed
                1.0f, //mass
                0.1f, // radius
                {1.0f, 1.0f, 1.0f} // colour
            );
        }
    }
}

