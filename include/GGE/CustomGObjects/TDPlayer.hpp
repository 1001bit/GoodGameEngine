#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

// Top-Down player
class TDPlayer : public KinematicBody
{
private:
    
public:
    // Structors
    TDPlayer();
    ~TDPlayer();

    // Methods
    // Control player
    void control();
};
