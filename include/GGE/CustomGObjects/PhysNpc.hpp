#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

class PhysNpc : public KinematicBody
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
    // npc movement
    void control();
};
