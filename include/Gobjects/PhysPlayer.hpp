#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

class PhysPlayer : public KinematicBody
{
private:
    static const float WALK_SPEED;
    static const float JUMP_FORCE;
    static const float AIR_SLOWDOWN;

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();

    // Methods
    // Control player
    void control();
};

}
