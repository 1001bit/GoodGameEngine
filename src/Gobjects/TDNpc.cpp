#include "Gobjects/TDNpc.hpp"

using gge::obj::TDNpc;

constexpr float WALK_SPEED = 4;

constexpr float IDLE_TIME = 2000;
constexpr float WALK_TIME = 3000;
constexpr float IDLE_RAND = 500;
constexpr float WALK_RAND = 1000;

// Structors
TDNpc::TDNpc(){
    movementDir = Direction::None;

    weighs = false;
    friction = true;
    collidable = true;
    controllable = true;
}
TDNpc::~TDNpc(){}

// Methods
// init cooldowns
void TDNpc::initCooldowns(CooldownsManager& cooldownsManager){
    idleCooldown = cooldownsManager.newCooldown(gge::Cooldown(IDLE_TIME));
    walkCooldown = cooldownsManager.newCooldown(gge::Cooldown(WALK_TIME));
    walkCooldown->start(WALK_RAND);
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
        idleCooldown->start(IDLE_RAND);
        return;
    }

    // if walking in collision direction - start idle and stop walk
    if(walkCooldown->getCurrentValueMs() && (movementDir == collisionDir.horizontal || movementDir == collisionDir.vertical)){
        movementDir = Direction::None;
        walkCooldown->stop();
        idleCooldown->start(IDLE_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!idleCooldown->getCurrentValueMs() && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 4 + 1);
        walkCooldown->start(WALK_RAND);
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Up:
        addAcceleration({0, -WALK_SPEED});
        break;
    case Direction::Down:
        addAcceleration({0, WALK_SPEED});
        break;
    case Direction::Left:
        addAcceleration({-WALK_SPEED, 0});
        break;
    case Direction::Right:
        addAcceleration({WALK_SPEED, 0});
        break;
    default:
        break;
    }
}