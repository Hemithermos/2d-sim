#include <iostream>
#include <chrono>

#include "platform/Window.h"
#include "renderer/Renderer.h"
#include "core/Coordinator.h"

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
int main()
{

    Window window(1280, 720, "Particle Engine");
    Renderer renderer(window.getWidth(), window.getHeight());
    window.setResizeCallback([&](int w, int h) {
        std::cout << "resize callback\n" << std::flush;
        renderer.resize((float)w, (float)h);
    });



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
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Force>());
        coordinator.setSystemSignature<ClearForcesSystem>(sig);
    }

    // Apply External forces : need forces and mass
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Mass>());
        sig.set(coordinator.getComponentType<Force>());
        coordinator.setSystemSignature<ApplyExternalForcesSystem>(sig);
    }

    // integrate velocity system : need forces, mass and velocity
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Mass>());
        sig.set(coordinator.getComponentType<Force>());
        sig.set(coordinator.getComponentType<Velocity>());
        coordinator.setSystemSignature<IntegrateVelocitySystem>(sig);
    }

    // integrate position system : need position and velocity
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Transform3D>());
        sig.set(coordinator.getComponentType<Velocity>());
        sig.set(coordinator.getComponentType<PreviousPosition>());
        coordinator.setSystemSignature<IntegratePositionSystem>(sig);
    }

    // floor collision system : need position and velocity
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Transform3D>());
        sig.set(coordinator.getComponentType<Velocity>());
        sig.set(coordinator.getComponentType<Spherical>());
        coordinator.setSystemSignature<FloorCollisionSystem>(sig);
    }

    // render system, need position, prevpos and renderparticle
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Transform3D>());
        sig.set(coordinator.getComponentType<PreviousPosition>());
        sig.set(coordinator.getComponentType<RenderParticle>());
        sig.set(coordinator.getComponentType<Spherical>());
        coordinator.setSystemSignature<RenderSystem>(sig);
    }

    // Particle collision system : pos, vel, mass, radius
    {
        Signature sig;
        sig.set(coordinator.getComponentType<Transform3D>());
        sig.set(coordinator.getComponentType<Velocity>());
        sig.set(coordinator.getComponentType<Spherical>());
        sig.set(coordinator.getComponentType<Mass>());
        coordinator.setSystemSignature<ParticleCollisionSystem>(sig);
    }



    Entity particle = coordinator.createEntity();

    coordinator.addComponent(particle, Transform3D{glm::vec3(0.0f, 1.0f, 0.0f)});
    coordinator.addComponent(particle, Velocity{glm::vec3(0.0f, 0.0f, 0.0f)});
    coordinator.addComponent(particle, Mass{1.0f});
    coordinator.addComponent(particle, Force{glm::vec3(0.0f, 0.0f, 0.0f)});
    coordinator.addComponent(particle, PreviousPosition{glm::vec3(0.0f, 1.0f, 0.0f)});
    coordinator.addComponent(particle, RenderParticle{});
    coordinator.addComponent(particle, Spherical{0.5f}); 
   
    Entity p2 = coordinator.createEntity();
    coordinator.addComponent(p2, Transform3D{glm::vec3(0.1f, 3.0f, 0.0f)});
    coordinator.addComponent(p2, Velocity{glm::vec3(0.0f, 0.0f, 0.0f)});
    coordinator.addComponent(p2, Mass{1.0f});
    coordinator.addComponent(p2, Force{glm::vec3(0.0f, 0.0f, 0.0f)});
    coordinator.addComponent(p2, PreviousPosition{glm::vec3(0.1f, 1.5f, 0.0f)});
    coordinator.addComponent(p2, RenderParticle{});
    coordinator.addComponent(p2, Spherical{0.5f}); 

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