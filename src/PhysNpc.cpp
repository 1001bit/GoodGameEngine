#include "PhysNpc.hpp"

constexpr float WALK_SPEED = 2;
constexpr float AIR_SLOWDOWN = 0.1;

constexpr float CHANGE_DIR_MIN_CD = 700;
constexpr int CHANGE_DIR_CD_RAND = 300;

// Structors
PhysNpc::PhysNpc(){
    npcType = Walking;
    movementDir = None;
    cooldownMap["idle"] = CHANGE_DIR_MIN_CD + rand() % CHANGE_DIR_CD_RAND;
}

PhysNpc::~PhysNpc(){}

// Methods
// Movement of the NPC
void PhysNpc::control(){
    float walkSpeed = WALK_SPEED;

    if(collisionVerticalDir != Down){
        walkSpeed *= AIR_SLOWDOWN;
    }

    // no movement while on idle cooldown
    if(cooldownMap.at("idle") != 0){
        return;
    }

    // if no direction - give one
    if(movementDir == None){
        movementDir = static_cast<Direction>(rand() % 2 + 3);
    }

    // if collision - start cooldown
    if(movementDir == collisionHorizontalDir || movementDir == collisionVerticalDir){
        movementDir = None;
        cooldownMap["idle"] = CHANGE_DIR_MIN_CD + rand() % CHANGE_DIR_CD_RAND;
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Left:
        acceleration.x -= walkSpeed;
        setFlip(1);
        break;
    case Right:
        acceleration.x += walkSpeed;
        setFlip(0);
        break;
    default:
        break;
    }
}