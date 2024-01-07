#include "PhysPlayer.hpp"
constexpr float WALK_SPEED = 2;
constexpr float JUMP_FORCE = 15;
constexpr float AIR_SLOWDOWN = 0.1;
constexpr float GROUND_FRICTION = 0.6;
constexpr float AIR_FRICTION = 0.95;

// Structors
PhysPlayer::PhysPlayer(){}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(){
    float walkSpeed = WALK_SPEED;
    if(collisionVerticalDir == Bottom){
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
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("jump")) && collisionVerticalDir == Bottom){
        acceleration.y -= JUMP_FORCE;
    }
}