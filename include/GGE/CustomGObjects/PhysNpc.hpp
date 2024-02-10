#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

class PhysNpc : public gge::KinematicBody
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    PhysNpc();
    ~PhysNpc();

    // Variables
    gge::NpcType npcType;

    // Methods
    // npc movement
    void control();
};
