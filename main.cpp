#include <iostream>
#include <chrono>

#include "platform/Window.h"
#include "renderer/Renderer.h"
#include "core/Coordinator.h"
#include "world.cpp"
// Components
#include "components/Transform3D.h"
#include "components/Velocity.h"
#include "components/Force.h"
#include "components/Mass.h"
#include "components/PreviousPosition.h"
#include "components/RenderParticle.h"
#include "components/Spherical.h"
// Systems
#include "systems/ClearForcesSystem.h"
#include "systems/ApplyExternalForcesSystem.h"
#include "systems/IntegrateVelocitySystem.h"
#include "systems/IntegratePositionSystem.h"
#include "systems/FloorCollisionSystem.h"
#include "systems/RenderSystem.h"
#include "systems/ParticleCollisionsSystem.h"
Coordinator coordinator;
constexpr float FIXED_DT = 1.0f / 60.0f;
constexpr float TIMESCALE = 1.0f;

template<typename... Components>
Signature makeSignature() {
    Signature sig;
    (sig.set(coordinator.getComponentType<Components>()), ...);
    return sig;
}

int main()
{

    Window window(1280, 720, "Particle Engine");
    Renderer renderer(window.getWidth(), window.getHeight());
    window.setResizeCallback([&](int w, int h) {
        std::cout << "resize callback\n" << std::flush;
        renderer.resize((float)w, (float)h);
    });


    // initialize the coordinator
    coordinator.init();

    // first let's register all of our components
    coordinator.registerComponent<Force>();
    coordinator.registerComponent<Transform3D>();
    coordinator.registerComponent<Velocity>();
    coordinator.registerComponent<Mass>();
    coordinator.registerComponent<PreviousPosition>();
    coordinator.registerComponent<RenderParticle>();
    coordinator.registerComponent<Spherical>();
    // now register the systems
    auto clearForceSystem = coordinator.registerSystem<ClearForcesSystem>();
    auto applyExternalForcesSystem = coordinator.registerSystem<ApplyExternalForcesSystem>();
    auto integrateVelocitySystem = coordinator.registerSystem<IntegrateVelocitySystem>(); 
    auto integratePositionSystem = coordinator.registerSystem<IntegratePositionSystem>();
    auto floorCollisionSystem = coordinator.registerSystem<FloorCollisionSystem>();
    auto renderSystem = coordinator.registerSystem<RenderSystem>(); 
    auto particleCollisionsSystem = coordinator.registerSystem<ParticleCollisionSystem>(); 
    // set signatures to each system

    // Clear forces : need forces
    coordinator.setSystemSignature<ClearForcesSystem>(makeSignature<Force>());
    // apply external forces : need forces and masses
    coordinator.setSystemSignature<ApplyExternalForcesSystem>(makeSignature<Mass, Force>());
    // integrate velocity system : need forces, mass and velocity
    coordinator.setSystemSignature<IntegrateVelocitySystem>(makeSignature<Mass, Force, Velocity>());
    // integrate position system : need position and velocity
    coordinator.setSystemSignature<IntegratePositionSystem>(makeSignature<Transform3D, Velocity, PreviousPosition>());
    // floor collision system : need position and velocity
    coordinator.setSystemSignature<FloorCollisionSystem>(makeSignature<Transform3D, Velocity, Spherical>());
    // render system, need position, prevpos and renderparticle
    coordinator.setSystemSignature<RenderSystem>(makeSignature<Transform3D, PreviousPosition, RenderParticle, Spherical>());
    // Particle collision system : pos, vel, mass, radius
    coordinator.setSystemSignature<ParticleCollisionSystem>(makeSignature<Transform3D, Velocity, Spherical, Mass>());
  


    // launch the initial world configuration
    World::init();

    // setup the clock
    float dt = 1.0f;
    float accumulator = 0.0f;
    auto previousTime = std::chrono::high_resolution_clock::now();


    while(window.isOpen()) {
        renderer.beginFrame(&window);
        auto currentTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float>(currentTime - previousTime).count();
        previousTime = currentTime;


        frameTime = std::min(frameTime, 0.25f);
        frameTime *= TIMESCALE;
        accumulator += frameTime;

        while (accumulator >= FIXED_DT) {
            clearForceSystem->update();
            applyExternalForcesSystem->update(FIXED_DT);
            integrateVelocitySystem->update(FIXED_DT);
            integratePositionSystem->update(FIXED_DT);

            floorCollisionSystem->update();
            particleCollisionsSystem->update(FIXED_DT);            
            

            accumulator -= FIXED_DT;
        }

        renderSystem->render(renderer, 1.0f);
        renderer.endFrame(&window);
    }

}