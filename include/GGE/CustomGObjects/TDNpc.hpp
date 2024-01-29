#pragma once

#include "GGE/GObjects/Body.hpp"

class TDNpc : public Body
{
private:
    // Variables
    Direction movementDir;

    // Methods
    // npc movement
    void control();
    
public:
    // Structors
    TDNpc();
    ~TDNpc();

    // Variables
    NpcType npcType;

    // Methods
    // update state
    void update(const float& dTimeMs);
};