#include "TDNpc.hpp"

constexpr float WALK_SPEED = 4;
constexpr float GROUND_FRICTION = 0.1;
constexpr unsigned MOVEMENT_RAND = 500;

// Structors
TDNpc::TDNpc(){
    npcType = NpcType::Walking;
    movementDir = Direction::None;
    
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
    if((!selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir != Direction::None)){
        movementDir = Direction::None;
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if collision and walking in collision direction - start idle and stop walk
    if(selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir == collisionHorizontalDir){
        movementDir = Direction::None;
        selfCooldownMap.at("walk")->stop();
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!selfCooldownMap.at("idle") && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 4 + 1);
        selfCooldownMap.at("walk")->start(1000);
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Up:
        acceleration.y -= WALK_SPEED;
        break;
    case Direction::Down:
        acceleration.y += WALK_SPEED;
        break;
    case Direction::Left:
        acceleration.x -= WALK_SPEED;
        break;
    case Direction::Right:
        acceleration.x += WALK_SPEED;
        break;
    default:
        break;
    }
}

// update state
void TDNpc::update(const float& timeMs){
    Body::update(timeMs);
    
    control();
};