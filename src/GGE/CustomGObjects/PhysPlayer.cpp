#include "GGE/CustomGObjects/PhysPlayer.hpp"

constexpr float WALK_SPEED = 2;
constexpr float JUMP_FORCE = 15;
constexpr float AIR_SLOWDOWN = 0.05;

// Structors
PhysPlayer::PhysPlayer(){
    weighs = 1;
    kinematic = 1;
    collidable = 0;
}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(){
    ControlsManager* controlsManager = ControlsManager::getInstance();

    float walkSpeed = WALK_SPEED;

    if(collisionDir.vertical != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // return;

    // walk left
    if(controlsManager->isControlHeld("wLeft")){
        accelerate(-walkSpeed, 0);
        setFlip(1);
    }

    // walk right
    if(controlsManager->isControlHeld("wRight")){
        accelerate(walkSpeed, 0);
        setFlip(0);
    }

    // jump
    if(controlsManager->isControlHeld("jump") && collisionDir.vertical == Direction::Down){
        accelerate(0, -JUMP_FORCE);
    }
}

// update state
void PhysPlayer::update(const float& dTimeMs){
    control();

    Body::update(dTimeMs);
};