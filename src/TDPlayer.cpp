#include "TDPlayer.hpp"

constexpr float WALK_SPEED = 15;
constexpr float GROUND_FRICTION = 0.1;

// Structors
TDPlayer::TDPlayer(){}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    ControlsManager* controlsManager = ControlsManager::getInstance();

    velocity *= GROUND_FRICTION;

    // walk left
    if(controlsManager->isControlHeld("wLeft")){
        acceleration.x -= WALK_SPEED;
    }
    // walk right
    if(controlsManager->isControlHeld("wRight")){
        acceleration.x += WALK_SPEED;
    }
    // walk up
    if(controlsManager->isControlHeld("wUp")){
        acceleration.y -= WALK_SPEED;
    }
    // walk down
    if(controlsManager->isControlHeld("wDown")){
        acceleration.y += WALK_SPEED;
    }
}

// update state
void TDPlayer::update(const float& timeMs){
    control();

    Body::update(timeMs);
};