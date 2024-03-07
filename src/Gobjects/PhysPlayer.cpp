#include "Gobjects/PhysPlayer.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::obj::PhysPlayer;

const float PhysPlayer::WALK_SPEED = 2;
const float PhysPlayer::JUMP_FORCE = 15;
const float PhysPlayer::AIR_SLOWDOWN = 0.05;

// Structors
PhysPlayer::PhysPlayer(){
    applyGravity = true;
    applyFriction = true;
    applyCollisions = true;
    applyControl = true;
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
        addAcceleration({-walkSpeed, 0});
        setFlip(1);
    }

    // walk right
    if(controlsManager->isHeld("wRight")){
        addAcceleration({walkSpeed, 0});
        setFlip(0);
    }

    // jump
    if(controlsManager->isHeld("jump") && collisionDir.vertical == Direction::Down){
        addAcceleration({0, -JUMP_FORCE});
    }
}