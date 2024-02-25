#include "GGECustom/Gobjects/PhysNpc.hpp"

using gge::obj::PhysNpc;

constexpr float WALK_SPEED = 2;
constexpr float AIR_SLOWDOWN = 0.05;
constexpr unsigned MOVEMENT_RAND = 500;

// Structors
PhysNpc::PhysNpc(){
    this->movementDir = Direction::None;

    this->weighs = 1;
    this->friction = 1;
    this->collidable = 1;
}

PhysNpc::~PhysNpc(){}

// Methods
// init cooldowns
void PhysNpc::initCooldowns(CooldownsManager& cooldownsManager){
    idleCooldown = cooldownsManager.newCooldown(gge::Cooldown(2000));
    walkCooldown = cooldownsManager.newCooldown(gge::Cooldown(3000));
    walkCooldown->start(500);
}

// Movement of the NPC
void PhysNpc::control(){
    // no movement while on idle cooldown
    if(idleCooldown->getCurrentValueMs()){
        return;
    }

    // if movement cooldown is over - start idle
    if((!walkCooldown->getCurrentValueMs() && movementDir != Direction::None)){
        movementDir = Direction::None;
        idleCooldown->start(MOVEMENT_RAND);
        return;
    }

    // if collision and walking in collision direction - start idle and stop walk
    if(walkCooldown->getCurrentValueMs() && movementDir == collisionDir.horizontal){
        movementDir = Direction::None;
        walkCooldown->stop();
        idleCooldown->start(MOVEMENT_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!idleCooldown->getCurrentValueMs() && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 2 + 3);
        walkCooldown->start(1000);
    }

    float walkSpeed = WALK_SPEED;
    if(collisionDir.vertical != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Left:
        accelerate(-walkSpeed, 0);
        setFlip(1);
        break;
    case Direction::Right:
        accelerate(walkSpeed, 0);
        setFlip(0);
        break;
    default:
        break;
    }
}