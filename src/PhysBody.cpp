#include "PhysBody.hpp"

constexpr float GFORCE = 0.08;
constexpr float GROUND_FRICTION = 0.6;
constexpr float AIR_FRICTION = 0.95;

// Structors
PhysBody::PhysBody(){}

PhysBody::~PhysBody(){}

// Methods
// Control
void PhysBody::control(){}
// Gravity impact
void PhysBody::gravity(const float& timeMs){
    acceleration.y += GFORCE * timeMs;

    // apply friction
    if(collisionVerticalDir == Down){
        velocity.x *= GROUND_FRICTION;
    } else {
        velocity.x *= AIR_FRICTION;
    }
}