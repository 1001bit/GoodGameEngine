#pragma once

#include "GGE/GObjects/Body.hpp"

class TDNpc : public Body
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
    // update state
    void update(const float& dTimeMs);
    // npc movement
    void control();
};