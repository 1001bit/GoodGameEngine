#pragma once

#include "PhysBody.hpp"

class PhysNpc : public PhysBody
{
private:
    // Variables
    Direction movementDir;
    NpcType npcType;

    // Methods
    // npc movement
    void control();
    
public:
    // Structors
    PhysNpc(/* args */);
    ~PhysNpc();
};
