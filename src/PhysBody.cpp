#include "PhysBody.hpp"

constexpr float GFORCE = 0.08;
constexpr float GROUND_FRICTION = 0.6;
constexpr float AIR_FRICTION = 0.96;

// Structors
PhysBody::PhysBody(){}

PhysBody::~PhysBody(){}

// Methods
// Gravity impact
void PhysBody::gravity(const float& timeMs){
    acceleration.y += GFORCE * timeMs;

    // apply friction
    if(collisionDir.vertical == Direction::Down){
        velocity.x *= GROUND_FRICTION;
    } else {
        velocity.x *= AIR_FRICTION;
    }
}

// update state
void PhysBody::update(const float& timeMs){
    gravity(timeMs);
    
    Body::update(timeMs);
};