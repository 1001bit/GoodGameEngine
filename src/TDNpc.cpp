#include "TDNpc.hpp"

constexpr float WALK_SPEED = 4;
constexpr float GROUND_FRICTION = 0.1;
constexpr float CHANGE_DIR_MIN_CD = 700;
constexpr int CHANGE_DIR_CD_RAND = 300;

// Structors
TDNpc::TDNpc(){
    npcType = Walking;
    movementDir = None;
    cooldownMap["idle"] = CHANGE_DIR_MIN_CD + rand() % CHANGE_DIR_CD_RAND;
}
TDNpc::~TDNpc(){}

// Methods
// npc movement
void TDNpc::control(){
    velocity *= GROUND_FRICTION;

    // no movement while on idle cooldown
    if(cooldownMap.at("idle") != 0){
        return;
    }

    // if no direction - give one
    if(movementDir == None){
        movementDir = static_cast<Direction>(rand() % 4 + 1);
    }

    // if collision - start cooldown
    if(movementDir == collisionHorizontalDir || movementDir == collisionVerticalDir){
        movementDir = None;
        cooldownMap["idle"] = CHANGE_DIR_MIN_CD + rand() % CHANGE_DIR_CD_RAND;
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