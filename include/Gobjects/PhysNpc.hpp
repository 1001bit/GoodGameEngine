#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Cooldowns/CooldownsManager.hpp"

namespace gge::obj {

class PhysNpc : public KinematicBody
{
private:
    static const float WALK_SPEED;
    static const float AIR_SLOWDOWN;

    static const float IDLE_TIME;
    static const float WALK_TIME;
    static const float IDLE_RAND;
    static const float WALK_RAND;

    Direction movementDir;
    std::shared_ptr<Cooldown> idleCooldown;
    std::shared_ptr<Cooldown> walkCooldown;

public:
    // Structors
    PhysNpc();
    ~PhysNpc();

    // Methods
    // npc movement
    void control();
    // init cooldowns
    void initCooldowns(CooldownsManager& cooldownsManager);
};

}