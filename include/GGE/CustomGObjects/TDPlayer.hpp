#pragma once

#include "GGE/GObjects/Body.hpp"

// Top-Down player
class TDPlayer : public Body
{
private:
    // Methods
    
public:
    // Structors
    TDPlayer();
    ~TDPlayer();

    // Methods
    // update state
    void update(const float& dTimeMs);
    // Control player
    void control();
};
