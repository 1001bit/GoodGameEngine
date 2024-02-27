#include "GGECustom/Gobjects/PhysPlayer.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::obj::PhysPlayer;

constexpr float WALK_SPEED = 2;
constexpr float JUMP_FORCE = 15;
constexpr float AIR_SLOWDOWN = 0.05;

// Structors
PhysPlayer::PhysPlayer(){
    this->weighs = 1;
    this->friction = 1;
    this->collidable = 1;
}

PhysPlayer::~PhysPlayer(){}

// Methods
// control the player
void PhysPlayer::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    float walkSpeed = WALK_SPEED;

    if(collisionDir.vertical != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // return;

    // walk left
    if(controlsManager->isHeld("wLeft")){
        accelerate(-walkSpeed, 0);
        setFlip(1);
    }

    // walk right
    if(controlsManager->isHeld("wRight")){
        accelerate(walkSpeed, 0);
        setFlip(0);
    }

    // jump
    if(controlsManager->isHeld("jump") && collisionDir.vertical == Direction::Down){
        accelerate(0, -JUMP_FORCE);
    }
}