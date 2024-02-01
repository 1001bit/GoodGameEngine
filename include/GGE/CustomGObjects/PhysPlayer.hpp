#pragma once

#include "GGE/GObjects/KinematicBody.hpp"
#include "unordered_map"

class PhysPlayer : public KinematicBody
{
private:

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();

    // Methods
    // update state
    void update(const float& dTimeMs);
    // Control player
    void control();
};
