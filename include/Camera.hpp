#pragma once

#include "GObject.hpp"

class Camera : public GObject
{
private:
    // Variables
    sf::View view;
    std::shared_ptr<GObject> followTarget;
    
public:
    // Structors
    Camera();
    ~Camera();

    // Methods
    // set size of view
    void setSize(float w, float h);
    // smoothly move camera
    void update(const float& timeMs);
    // set target of following
    void setTarget(std::shared_ptr<GObject> newTarget);

    // Getters
    // get view
    const sf::View& getView();
};
