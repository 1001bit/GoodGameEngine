#include "GGE/CustomGObjects/PhysNpc.hpp"

constexpr float WALK_SPEED = 2;
constexpr float AIR_SLOWDOWN = 0.05;
constexpr unsigned MOVEMENT_RAND = 500;

// Structors
PhysNpc::PhysNpc(){
    npcType = NpcType::Walking;
    movementDir = Direction::None;

    weighs = 1;
    collidable = 1;

    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    selfCooldownMap["idle"] = cooldownsManager->newCooldown(Cooldown(2000));
    selfCooldownMap["walk"] = cooldownsManager->newCooldown(Cooldown(3000));
    selfCooldownMap.at("idle")->start(500);
}

PhysNpc::~PhysNpc(){}

// Methods
// Movement of the NPC
void PhysNpc::control(){
    // no movement while on idle cooldown
    if(selfCooldownMap.at("idle")->getCurrentValueMs()){
        return;
    }

    // if movement cooldown is over - start idle
    if((!selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir != Direction::None)){
        movementDir = Direction::None;
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if collision and walking in collision direction - start idle and stop walk
    if(selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir == collisionDir.horizontal){
        movementDir = Direction::None;
        selfCooldownMap.at("walk")->stop();
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!selfCooldownMap.at("idle")->getCurrentValueMs() && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 2 + 3);
        selfCooldownMap.at("walk")->start(1000);
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

// update state
void PhysNpc::update(const float& dTimeMs){
    Body::update(dTimeMs);
};