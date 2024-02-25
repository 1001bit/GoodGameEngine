#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

class PhysNpc : public KinematicBody
{
private:
    // Variables
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