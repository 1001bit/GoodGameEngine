#include "Gobjects/TDPlayer.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::obj::TDPlayer;

constexpr float WALK_SPEED = 15;

// Structors
TDPlayer::TDPlayer(){
    weighs = false;
    friction = true;
    collidable = true;
    controllable = true;
}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    // walk left
    if(controlsManager->isHeld("wLeft")){
        accelerate(-WALK_SPEED, 0);
    }
    // walk right
    if(controlsManager->isHeld("wRight")){
        accelerate(WALK_SPEED, 0);
    }
    // walk up
    if(controlsManager->isHeld("wUp")){
        accelerate(0, -WALK_SPEED);
    }
    // walk down
    if(controlsManager->isHeld("wDown")){
        accelerate(0, WALK_SPEED);
    }
}