#pragma once

#include "GObject.hpp"
#include <GGE/MathHelper.hpp>

class Camera : public GObject
{
private:
    // Variables
    sf::View view;
    std::weak_ptr<GObject> followTargetWeak;
    
public:
    // Structors
    Camera();
    ~Camera();

    // Methods
    // set size of view
    void setSize(float w, float h);
    // smoothly move camera
    void update(const float& dTimeMs);
    // set target of following
    void setTarget(std::shared_ptr<GObject> newTarget);

    // Getters
    // get view
    const sf::View& getView();
};
