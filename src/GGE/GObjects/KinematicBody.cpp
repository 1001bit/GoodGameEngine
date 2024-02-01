#include "GGE/GObjects/KinematicBody.hpp"

// Structors
KinematicBody::KinematicBody(){
    weighs = 0;
    collisionDir = {Direction::None, Direction::None};
}
KinematicBody::~KinematicBody(){}

// Methods
// Control the body
void KinematicBody::control(){}

// Accelerate the body
void KinematicBody::accelerate(float accelX, float accelY){
    acceleration.x += accelX;
    acceleration.y += accelY;
}

void KinematicBody::setCurrentPosition(sf::Vector2f newPosition){
    currentRect.left = newPosition.x;
    currentRect.top = newPosition.y;
}

// Move the current rect
void KinematicBody::moveCurrentRect(sf::Vector2f moveDistance){
    setCurrentPosition(currentRect.getPosition() + moveDistance);
}

// set size of current rect
void KinematicBody::setRectSize(float w, float h){
    currentRect.width = w;
    currentRect.height = h;

    GObject::setRectSize(w, h);
}

// Getters
// weighs
const bool& KinematicBody::doesWeigh(){
    return weighs;
}

// acceleration
const sf::Vector2f& KinematicBody::getAcceleration(){
    return acceleration;
};