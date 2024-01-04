#include "PhysBody.hpp"

constexpr float GFORCE = 0.08;

// Structors
PhysBody::PhysBody(){}

PhysBody::~PhysBody(){}

// Methods
// Control
void PhysBody::control(const float& timeMs){}
// Gravity impact
void PhysBody::gravity(const float& timeMs){
    velocity.y += GFORCE * timeMs;
}