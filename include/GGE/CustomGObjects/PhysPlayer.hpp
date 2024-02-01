#pragma once

#include "GGE/GObjects/Body.hpp"
#include "unordered_map"

class PhysPlayer : public Body
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
