#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

class PhysNpc : public KinematicBody
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    PhysNpc();
    ~PhysNpc();

    // Methods
    // npc movement
    void control();
};

}