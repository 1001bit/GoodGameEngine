#include "PhysPlayer.hpp"
constexpr float WALK_SPEED = 4;
constexpr float JUMP_FORCE = 15;
constexpr float AIR_SLOWDOWN = 0.05;
constexpr float GROUND_FRICTION = 0.05;
constexpr float AIR_FRICTION = 0.95;

// Structors
PhysPlayer::PhysPlayer(){}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(){
    float walkSpeed = WALK_SPEED;
    if(collisionVerticalDir == bottom){
        velocity.x *= GROUND_FRICTION;
    } else {
        velocity.x *= AIR_FRICTION;
        walkSpeed *= AIR_SLOWDOWN;
    }

    // walk left
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wLeft"))){
        acceleration.x -= walkSpeed;
    }
    // walk right
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wRight"))){
        acceleration.x += walkSpeed;
    }

    // jump
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("jump")) && collisionVerticalDir == bottom){
        acceleration.y -= JUMP_FORCE;
    }
}