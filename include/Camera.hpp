#pragma once

#include "GObject.hpp"

class Camera : public GObject
{
private:
    // Variables
    sf::View view;
    
public:
    // Structors
    Camera();
    ~Camera();

    // Methods
    // set size of view
    void setSize(float w, float h);
    // smoothly move camera
    void update(const float& timeMs);

    // Getters
    // get view
    const sf::View& getView();
};
