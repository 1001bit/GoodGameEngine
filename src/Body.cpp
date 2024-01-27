#include "Body.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
Body::Body(){
    solid = 0;
    collisionDir = {Direction::None, Direction::None};
}

Body::~Body(){}

// Methods
// Update the state
void Body::update(const float& timeMs){
    velocity += acceleration * ACCEL_COEFF * timeMs;
    acceleration = sf::Vector2f();

    move(velocity);

    GObject::update(timeMs);
};