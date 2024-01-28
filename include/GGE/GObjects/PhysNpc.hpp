#pragma once

#include "Body.hpp"

class PhysNpc : public Body
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
    void update(const float& dTimeMs);
};
