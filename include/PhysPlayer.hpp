#pragma once

#include "PhysBody.hpp"
#include "unordered_map"

class PhysPlayer : public PhysBody
{
private:
    // Methods
    // Control your character
    void control();

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();
};
