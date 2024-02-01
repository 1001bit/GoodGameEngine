#pragma once

#include "GGE/GObjects/Body.hpp"

class PhysNpc : public Body
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    PhysNpc();
    ~PhysNpc();

    // Variables
    NpcType npcType;

    // Methods
    // update state
    void update(const float& dTimeMs);
    // npc movement
    void control();
};
