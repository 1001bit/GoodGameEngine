#pragma once

#include "GGE/GObjects/KinematicBody.hpp"
#include "GGE/Controls/ControlsManager.hpp"

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