#include "TDPlayer.hpp"

constexpr float WALK_SPEED = 4;
constexpr float GROUND_FRICTION = 0.1;

// Structors
TDPlayer::TDPlayer(){}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    velocity *= GROUND_FRICTION;

    // walk left
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wLeft"))){
        acceleration.x -= WALK_SPEED;
    }
    // walk right
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wRight"))){
        acceleration.x += WALK_SPEED;
    }
    // walk up
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wUp"))){
        acceleration.y -= WALK_SPEED;
    }
    // walk down
    if(sf::Keyboard::isKeyPressed(movementControlsMap.at("wDown"))){
        acceleration.y += WALK_SPEED;
    }
}