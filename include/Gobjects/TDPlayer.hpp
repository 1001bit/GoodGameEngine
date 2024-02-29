#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

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

}