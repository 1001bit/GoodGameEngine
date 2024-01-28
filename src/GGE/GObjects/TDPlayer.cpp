#include "GGE/GObjects/TDPlayer.hpp"

constexpr float WALK_SPEED = 15;

// Structors
TDPlayer::TDPlayer(){
    weighs = 0;
    kinematic = 1;
    collidable = 0;
}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    ControlsManager* controlsManager = ControlsManager::getInstance();

    // walk left
    if(controlsManager->isControlHeld("wLeft")){
        accelerate(-WALK_SPEED, 0);
    }
    // walk right
    if(controlsManager->isControlHeld("wRight")){
        accelerate(WALK_SPEED, 0);
    }
    // walk up
    if(controlsManager->isControlHeld("wUp")){
        accelerate(0, -WALK_SPEED);
    }
    // walk down
    if(controlsManager->isControlHeld("wDown")){
        accelerate(0, WALK_SPEED);
    }
}

// update state
void TDPlayer::update(const float& dTimeMs){
    control();

    Body::update(dTimeMs);
};