#include "TDNpc.hpp"

constexpr float WALK_SPEED = 4;
constexpr float GROUND_FRICTION = 0.1;
constexpr float CHANGE_DIR_MIN_CD = 700;
constexpr int CHANGE_DIR_CD_RAND = 300;

// Structors
TDNpc::TDNpc(){
    npcType = Walking;
    movementDir = None;
    
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    selfCooldownMap["idle"] = cooldownsManager->newCooldown(2000);
    selfCooldownMap["walk"] = cooldownsManager->newCooldown(3000);
}
TDNpc::~TDNpc(){}

// Methods
// npc movement
void TDNpc::control(){
    velocity *= GROUND_FRICTION;

    // no movement while on idle cooldown
    if(selfCooldownMap.at("idle")->getCurrentValueMs()){
        return;
    }

    // if movement cooldown is over - start idle
    if((!selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir != None)){
        movementDir = None;
        selfCooldownMap.at("idle")->start(500);
        return;
    }

    // if collision and walking in collision direction - start idle
    if(selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir == collisionHorizontalDir){
        movementDir = None;
        selfCooldownMap.at("idle")->start(500);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!selfCooldownMap.at("idle") && movementDir == None){
        movementDir = static_cast<Direction>(rand() % 4 + 1);
        selfCooldownMap.at("walk")->start(1000);
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Up:
        acceleration.y -= WALK_SPEED;
        break;
    case Down:
        acceleration.y += WALK_SPEED;
        break;
    case Left:
        acceleration.x -= WALK_SPEED;
        break;
    case Right:
        acceleration.x += WALK_SPEED;
        break;
    default:
        break;
    }
}

// set new type of npc
void TDNpc::setType(NpcType newType){
    npcType = newType;
}