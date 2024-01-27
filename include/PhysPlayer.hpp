#pragma once

#include "Body.hpp"
#include "unordered_map"

class PhysPlayer : public Body
{
private:
    // Methods
    // Control your character
    void control();

public:
    // Structors
    PhysPlayer();
    ~PhysPlayer();

    // Methods
    // update state
    void update(const float& timeMs);
};
