#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

// Top-Down player
class TDPlayer : public KinematicBody
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
