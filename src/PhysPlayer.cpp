#include "PhysPlayer.hpp"
constexpr float WALK_SPEED = 0.5;
constexpr float JUMP_FORCE = 25;
constexpr float AIR_SLOWDOWN = 0.05;
constexpr float GROUND_FRICTION = 0.05;
constexpr float AIR_FRICTION = 0.95;

// Structors
PhysPlayer::PhysPlayer(){}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(const float& timeMs){
    float walkSpeed = WALK_SPEED * timeMs;
    if(collisionVerticalDir == bottom){
        velocity.x *= GROUND_FRICTION;
    } else {
        velocity.x *= AIR_FRICTION;
        walkSpeed *= AIR_SLOWDOWN;
    }

    // walk left
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wLeft"))){
        velocity.x -= walkSpeed;
    }
    // walk right
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wRight"))){
        velocity.x += walkSpeed;
    }

    // jump
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("jump")) && collisionVerticalDir == bottom){
        velocity.y -= JUMP_FORCE;
    }
}