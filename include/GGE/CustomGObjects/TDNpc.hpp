#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

class TDNpc : public gge::KinematicBody
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    TDNpc();
    ~TDNpc();

    // Methods
    // npc movement
    void control();
};