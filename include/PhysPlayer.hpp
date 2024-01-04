#pragma once

#include "PhysBody.hpp"
#include "unordered_map"

class PhysPlayer : public PhysBody
{
private:
    // Methods
    // Control your character
    void control(const float& timeMs);

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();
};
