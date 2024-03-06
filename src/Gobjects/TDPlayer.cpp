#include "Gobjects/TDPlayer.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::obj::TDPlayer;

const float TDPlayer::WALK_SPEED = 15;

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
        addAcceleration({-WALK_SPEED, 0});
    }
    // walk right
    if(controlsManager->isHeld("wRight")){
        addAcceleration({WALK_SPEED, 0});
    }
    // walk up
    if(controlsManager->isHeld("wUp")){
        addAcceleration({0, -WALK_SPEED});
    }
    // walk down
    if(controlsManager->isHeld("wDown")){
        addAcceleration({0, WALK_SPEED});
    }
}