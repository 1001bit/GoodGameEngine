#include "Body.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
Body::Body(){
    solid = 1;
    weighs = 0;
    collisionDir = {Direction::None, Direction::None};
}

Body::~Body(){}

// Methods
// Update the state
void Body::update(const float& timeMs){
    velocity += acceleration * ACCEL_COEFF * timeMs;
    acceleration = sf::Vector2f();

    GObject::update(timeMs);
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