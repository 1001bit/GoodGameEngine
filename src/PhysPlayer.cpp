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
    ControlsManager* controls = ControlsManager::getInstance();

    float walkSpeed = WALK_SPEED;

    if(collisionVerticalDir != Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // walk left
    if(controls->isControlHeld("wLeft")){
        acceleration.x -= walkSpeed;
    }
    // walk right
    if(controls->isControlHeld("wRight")){
        acceleration.x += walkSpeed;
    }

    // jump
    if(controls->isControlPressedOnce("jump") && collisionVerticalDir == Down){
        acceleration.y -= JUMP_FORCE;
    }
}