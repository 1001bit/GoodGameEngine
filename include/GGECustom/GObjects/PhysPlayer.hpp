#pragma once

#include "GGE/GObjects/KinematicBody.hpp"
#include "GGE/Controls/ControlsManager.hpp"

namespace gge::obj {

class PhysPlayer : public KinematicBody
{
private:

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();

    // Methods
    // Control player
    void control();
};

}
