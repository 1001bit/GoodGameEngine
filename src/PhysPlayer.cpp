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
        setFlip(1);
    }
    // walk right
    if(controls->isControlHeld("wRight")){
        acceleration.x += walkSpeed;
        setFlip(0);
    }

    // jump
    if(controls->isControlHeld("jump") && collisionVerticalDir == Down){
        acceleration.y -= JUMP_FORCE;
    }
}