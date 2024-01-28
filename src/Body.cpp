#include "Body.hpp"

// Structors
Body::Body(){
    solid = 1;
    weighs = 0;
    collisionDir = {Direction::None, Direction::None};
}

Body::~Body(){}

// Methods
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
const bool& Body::isSolid(){
    return solid;
}
// acceleration
const sf::Vector2f& Body::getAcceleration(){
    return acceleration;
};