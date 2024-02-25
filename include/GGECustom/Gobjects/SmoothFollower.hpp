#pragma once

#include "GGE/Gobjects/Gobject.hpp"

namespace gge::obj {

class SmoothFollower : public Gobject
{
private:
    // Variables
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