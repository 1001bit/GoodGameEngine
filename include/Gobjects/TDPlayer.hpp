#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

class TDPlayer : public KinematicBody
{
private:
    static const float WALK_SPEED;
    
public:
    // Structors
    TDPlayer();
    ~TDPlayer();

    // Methods
    // Control player
    void control();
};

}