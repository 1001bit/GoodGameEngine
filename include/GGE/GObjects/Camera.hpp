#pragma once

#include "GObject.hpp"
#include "View.hpp"
#include <GGE/MathHelper.hpp>

namespace gge::obj {

class Camera : public GObject
{
private:
    // Variables
    std::weak_ptr<GObject> followTargetWeak;

    // Methods
    // update position of rect and camera
    void updatePos();
    
public:
    // Structors
    Camera();
    ~Camera();

    // Variables
    View view;

    // Methods
    // set size of view
    void setRectSize(float w, float h);
    // smoothly move camera
    void update(const float& dTimeMs);
    // set target of following
    void setTarget(std::shared_ptr<GObject> newTarget);
};

}