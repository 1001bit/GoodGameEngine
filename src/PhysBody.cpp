#include "PhysBody.hpp"
#include <iostream>

constexpr float GFORCE = 0.08;

// Structors
PhysBody::PhysBody(){
    this->type = gPhysBody;
}

PhysBody::~PhysBody(){}

// Methods
// Update
void PhysBody::update(const float& timeMs){
    control();
    gravity(timeMs);
    setRelativePos(getRelativePos() + velocity);
}
// Gravity impact
void PhysBody::gravity(const float& timeMs){
    velocity.y += GFORCE * timeMs;
}
// Control
void PhysBody::control(){}
