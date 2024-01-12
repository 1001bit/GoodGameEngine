#include "TDPlayer.hpp"

constexpr float WALK_SPEED = 15;
constexpr float GROUND_FRICTION = 0.1;

// Structors
TDPlayer::TDPlayer(){}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    ControlsManager* controls = ControlsManager::getInstance();

    velocity *= GROUND_FRICTION;

    // walk left
    if(controls->isControlHeld("wLeft")){
        acceleration.x -= WALK_SPEED;
    }
    // walk right
    if(controls->isControlHeld("wRight")){
        acceleration.x += WALK_SPEED;
    }
    // walk up
    if(controls->isControlHeld("wUp")){
        acceleration.y -= WALK_SPEED;
    }
    // walk down
    if(controls->isControlHeld("wDown")){
        acceleration.y += WALK_SPEED;
    }
}