#pragma once

#include "KinematicBody.hpp"

// Top-Down player
class TDPlayer : public KinematicBody
{
private:
    // Methods
    // control your character
    void control();

public:
    // Structors
    TDPlayer();
    ~TDPlayer();
};
