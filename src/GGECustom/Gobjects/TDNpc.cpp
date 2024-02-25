#include "GGECustom/Gobjects/TDNpc.hpp"

using gge::obj::TDNpc;

constexpr float WALK_SPEED = 4;
constexpr unsigned MOVEMENT_RAND = 500;

// Structors
TDNpc::TDNpc(){
    this->movementDir = Direction::None;

    this->weighs = false;
    this->friction = true;
    this->collidable = true;
}
TDNpc::~TDNpc(){}

// Methods
// init cooldowns
void TDNpc::initCooldowns(CooldownsManager& cooldownsManager){
    idleCooldown = cooldownsManager.newCooldown(gge::Cooldown(2000));
    walkCooldown = cooldownsManager.newCooldown(gge::Cooldown(3000));
    walkCooldown->start(500);
}

// npc movement
void TDNpc::control(){
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
        movementDir = static_cast<Direction>(rand() % 4 + 1);
        walkCooldown->start(1000);
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Up:
        accelerate(0, -WALK_SPEED);
        break;
    case Direction::Down:
        accelerate(0, WALK_SPEED);
        break;
    case Direction::Left:
        accelerate(-WALK_SPEED, 0);
        break;
    case Direction::Right:
        accelerate(WALK_SPEED, 0);
        break;
    default:
        break;
    }
}