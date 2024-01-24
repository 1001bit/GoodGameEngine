#include "PhysPlayer.hpp"

constexpr float WALK_SPEED = 2;
constexpr float JUMP_FORCE = 15;
constexpr float AIR_SLOWDOWN = 0.1;

// Structors
PhysPlayer::PhysPlayer(){}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(){
    ControlsManager* controlsManager = ControlsManager::getInstance();

    float walkSpeed = WALK_SPEED;

    if(collisionVerticalDir != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // walk left
    if(controlsManager->isControlHeld("wLeft")){
        acceleration.x -= walkSpeed;
        setFlip(1);
    }
    // walk right
    if(controlsManager->isControlHeld("wRight")){
        acceleration.x += walkSpeed;
        setFlip(0);
    }

    // jump
    if(controlsManager->isControlHeld("jump") && collisionVerticalDir == Direction::Down){
        acceleration.y -= JUMP_FORCE;
    }
}