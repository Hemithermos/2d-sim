#include "FloorCollisionSystem.h"
#include "../core/Coordinator.h"
#include "../components/Transform3D.h"
#include "../components/Velocity.h"
#include "../components/Spherical.h"

extern Coordinator coordinator;

constexpr float Y_FLOOR = -4.5f;
constexpr float Y_CEILING = 4.5f;
constexpr float LEFT_WALL = -8.0f;
constexpr float RIGHT_WALL = 8.0f;
constexpr float RESTITUTION = 1.0f;


void FloorCollisionSystem::update()
{
    for(Entity e : listOfEntities) {
        auto& pos = coordinator.getComponent<Transform3D>(e);
        auto& vel = coordinator.getComponent<Velocity>(e);
        auto& rad = coordinator.getComponent<Spherical>(e);

        if(pos.position.y - rad.radius < Y_FLOOR) {
            pos.position.y = Y_FLOOR + rad.radius;
            if(vel.velocity.y < 0.0f)
                vel.velocity.y = -vel.velocity.y * RESTITUTION;
            
        }
        else if(pos.position.y + rad.radius > Y_CEILING) {
            pos.position.y = Y_CEILING - rad.radius;
            if(vel.velocity.y > 0.0f)
                vel.velocity.y = - vel.velocity.y * RESTITUTION;
            return;
        }

        if(pos.position.x - rad.radius < LEFT_WALL) {
            pos.position.x = LEFT_WALL + rad.radius;
            if(vel.velocity.x < 0.0f)
                vel.velocity.x = -vel.velocity.x * RESTITUTION;
        }
        else if(pos.position.x + rad.radius > RIGHT_WALL) {
            pos.position.x = RIGHT_WALL - rad.radius;
            if(vel.velocity.x > 0.0f)
                vel.velocity.x = -vel.velocity.x * RESTITUTION;
            return;
        }

    }
}