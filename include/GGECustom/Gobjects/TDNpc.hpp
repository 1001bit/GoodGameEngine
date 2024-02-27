#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Cooldowns/CooldownsManager.hpp"

namespace gge::obj {

class TDNpc : public KinematicBody
{
private:
    Direction movementDir;
    std::shared_ptr<Cooldown> idleCooldown;
    std::shared_ptr<Cooldown> walkCooldown;

public:
    // Structors
    TDNpc();
    ~TDNpc();

    // Methods
    // npc movement
    void control();
    // init cooldowns
    void initCooldowns(CooldownsManager& cooldownsManager);
};

}