#include "core/Coordinator.h"
#include "components/Transform3D.h"
#include "components/Velocity.h"
#include "components/Force.h"
#include "components/Mass.h"
#include "components/PreviousPosition.h"
#include "components/RenderParticle.h"
#include "components/Spherical.h" 
#include "core/Entity.h"
#include <random>

extern Coordinator coordinator;

namespace World {



    void spawnParticle(glm::vec3 pos, glm::vec3 vel, float m, float radius, glm::vec3 color = {1.0f, 0.0f, 0.0f}, glm::vec3 f = {0.0f, 0.0f, 0.0f}) {
        Entity particle = coordinator.createEntity();

        coordinator.addComponent(particle, Transform3D{pos});
        coordinator.addComponent(particle, Velocity{vel});
        coordinator.addComponent(particle, Mass{m});
        coordinator.addComponent(particle, Force{f});
        coordinator.addComponent(particle, PreviousPosition{pos});
        coordinator.addComponent(particle, RenderParticle{glm::vec4(color, 1.0f)});
        coordinator.addComponent(particle, Spherical{radius}); 
    }
    
    
    
    
    
    
    
    
    
    
    
    void init() {
        std::default_random_engine generator;
        std::uniform_real_distribution<float> distribution (-0.01f, 0.01f);
        for(float i = -7.5 ; i <= 7.5 ; i+=2) {
            for(float j = -3.5 ; j <= 4.5 ; j+=1) {
                float a = distribution(generator);
                spawnParticle({i + a, j + a, 0.0f}, {0.0f, 0.0f, 0.0f}, 1.0f, 0.3f, {2*(i+7.5f)/30.0f , 2*(j+3.5f)/14.0f, 1.0f});
            }
        }
    }


}