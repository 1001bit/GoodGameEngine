#include "GGE/GObjects/Body.hpp"

// Structors
Body::Body(){
    collidable = 1;
    kinematic = 0;
    weighs = 0;
    collisionDir = {Direction::None, Direction::None};
}

Body::~Body(){}

// Methods
// Control the body
void Body::control(){}

// Update the state
void Body::update(const float& dTimeMs){
    GObject::update(dTimeMs);
};

// Accelerate the body
void Body::accelerate(float accelX, float accelY){
    acceleration.x += accelX;
    acceleration.y += accelY;
};

// Getters
// weighs
const bool& Body::doesWeigh(){
    return weighs;
}
// solid
const bool& Body::isKinematic(){
    return kinematic;
}
// collidable
const bool& Body::isCollidable(){
    return collidable;
};
// acceleration
const sf::Vector2f& Body::getAcceleration(){
    return acceleration;
};