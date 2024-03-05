#include "Gobjects/PhysNpc.hpp"

using gge::obj::PhysNpc;

constexpr float WALK_SPEED = 2;
constexpr float AIR_SLOWDOWN = 0.05;

constexpr float IDLE_TIME = 2000;
constexpr float WALK_TIME = 3000;
constexpr float IDLE_RAND = 500;
constexpr float WALK_RAND = 1000;

// Structors
PhysNpc::PhysNpc(){
    movementDir = Direction::None;

    weighs = true;
    friction = true;
    collidable = true;
    controllable = true;
}

PhysNpc::~PhysNpc(){}

// Methods
// init cooldowns
void PhysNpc::initCooldowns(CooldownsManager& cooldownsManager){
    idleCooldown = cooldownsManager.newCooldown(gge::Cooldown(IDLE_TIME));
    walkCooldown = cooldownsManager.newCooldown(gge::Cooldown(WALK_TIME));
    walkCooldown->start(WALK_RAND);
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
        idleCooldown->start(IDLE_RAND);
        return;
    }

    // if walking in collision direction - start idle and stop walk
    if(walkCooldown->getCurrentValueMs() && movementDir == collisionDir.horizontal){
        movementDir = Direction::None;
        walkCooldown->stop();
        idleCooldown->start(IDLE_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!idleCooldown->getCurrentValueMs() && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 2 + 3);
        walkCooldown->start(WALK_RAND);
    }

    float walkSpeed = WALK_SPEED;
    if(collisionDir.vertical != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Left:
        addAcceleration({-walkSpeed, 0});
        setFlip(1);
        break;
    case Direction::Right:
        addAcceleration({walkSpeed, 0});
        setFlip(0);
        break;
    default:
        break;
    }
}