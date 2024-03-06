#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::obj {

class SmoothFollower : public KinematicBody 
{
private:
    static const float APPROACH_FACTOR;

    std::weak_ptr<Gobject> followTargetWeak;
    
public:
    // Structors
    SmoothFollower();
    ~SmoothFollower();

    // Methods
    // smoothly move camera
    void update(const float& dTimeMs);
    // set target of following
    void setTarget(std::shared_ptr<Gobject> newTarget);
};

}