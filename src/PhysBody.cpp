#include "PhysBody.hpp"
#include <iostream>

constexpr float GFORCE = 0.08;

// Functions
sf::FloatRect getCollisionOverlap(const sf::FloatRect& a, const sf::FloatRect& b){
    sf::FloatRect overlap;
    a.intersects(b, overlap);
    return overlap;
}

// Structors
PhysBody::PhysBody(){
    this->type = gPhysBody;
}

PhysBody::~PhysBody(){}

// Methods
// Control
void PhysBody::control(){}
// Update physics and movement state
void PhysBody::update(const float& timeMs){
    control();
    gravity(timeMs);
    setRelativePos(getRelativePos() + velocity);
}
// Gravity impact
void PhysBody::gravity(const float& timeMs){
    velocity.y += GFORCE * timeMs;
}
// behaviour on collide
void PhysBody::collide(std::shared_ptr<GObject> obstacle){
    const sf::FloatRect& selfRect = getCollider();
    const sf::FloatRect& obstacleRect = obstacle->getCollider();
    // only solid body can stop physics body | no collision if no collision!
    if(obstacle->getType() != gSolidBody || !(selfRect.intersects(obstacleRect))){
        return;
    }

    sf::FloatRect overlap = getCollisionOverlap(selfRect, obstacleRect);

    // Horizontal 
    if(overlap.width < overlap.height){
        // right
        if(selfRect.left < obstacleRect.left){
            setRelativePos(obstacleRect.left-selfRect.width, getRelativePos().y);
        }
        // left
        else {
            setRelativePos(obstacleRect.left + obstacleRect.width, getRelativePos().y);
        }
        velocity.x = 0;
    } 
    // Vertical
    else {
        // top
        if(selfRect.top < obstacleRect.top){
            setRelativePos(getRelativePos().x, obstacleRect.top - selfRect.height);
        } 
        // bottom
        else {
            setRelativePos(getRelativePos().x, obstacleRect.top + obstacleRect.height);
        }
        velocity.y = 0;
    }
}