#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

class PhysPlayer : public gge::KinematicBody
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
