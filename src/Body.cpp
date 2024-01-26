#include "Body.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
Body::Body(){
    solid = 0;
    collisionHorizontalDir = Direction::None;
    collisionVerticalDir = Direction::None;
}

Body::~Body(){}

// Methods
// Update the state
void Body::update(const float& timeMs){
    velocity += acceleration * ACCEL_COEFF * timeMs;
    move(velocity);

    // nullify all
    acceleration = sf::Vector2f();

    GObject::update(timeMs);
};