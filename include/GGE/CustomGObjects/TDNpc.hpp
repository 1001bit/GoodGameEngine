#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

class TDNpc : public KinematicBody
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    TDNpc();
    ~TDNpc();

    // Variables
    NpcType npcType;

    // Methods
    // npc movement
    void control();
};