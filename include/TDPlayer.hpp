#pragma once

#include "Body.hpp"

// Top-Down player
class TDPlayer : public Body
{
private:
    // Methods
    // control your character
    void control();
    
public:
    // Structors
    TDPlayer();
    ~TDPlayer();

    // Methods
    // update state
    void update(const float& timeMs);
};
