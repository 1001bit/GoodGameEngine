#include "PhysNpc.hpp"

constexpr float WALK_SPEED = 2;
constexpr float AIR_SLOWDOWN = 0.1;

constexpr float CHANGE_DIR_MIN_CD = 700;
constexpr int CHANGE_DIR_CD_RAND = 300;

// Structors
PhysNpc::PhysNpc(){
    npcType = Walking;
    movementDir = Direction::None;

    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    selfCooldownMap["idle"] = cooldownsManager->newCooldown(2000);
    selfCooldownMap["walk"] = cooldownsManager->newCooldown(3000);
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
        selfCooldownMap.at("idle")->start(500);
        return;
    }

    // if collision and walking in collision direction - start idle and stop walk
    if(selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir == collisionHorizontalDir){
        movementDir = Direction::None;
        selfCooldownMap.at("walk")->stop();
        selfCooldownMap.at("idle")->start(500);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!selfCooldownMap.at("idle")->getCurrentValueMs() && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 2 + 3);
        selfCooldownMap.at("walk")->start(1000);
    }

    float walkSpeed = WALK_SPEED;
    if(collisionVerticalDir != Direction::Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Left:
        acceleration.x -= walkSpeed;
        setFlip(1);
        break;
    case Direction::Right:
        acceleration.x += walkSpeed;
        setFlip(0);
        break;
    default:
        break;
    }
}