#pragma once

#include "PhysBody.hpp"

class PhysNpc : public PhysBody
{
private:
    // Variables
    Direction movementDir;

    // Methods
    // npc movement
    void control();
    
public:
    // Structors
    PhysNpc();
    ~PhysNpc();

    // Variables
    NpcType npcType;

    // Methods
    // update state
    void update(const float& timeMs);
};
