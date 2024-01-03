#pragma once

#include "GObject.hpp"

class Camera : public GObject
{
private:
    // Variables
    std::shared_ptr<GObject> subject;
    sf::View view;
    
public:
    // Structors
    Camera();
    ~Camera();

    // Methods
    // set size of view
    void setSize(float w, float h);
    // set subject to follow
    void setSubject(std::shared_ptr<GObject> newSubject);
    // smoothly move camera
    void update(const float& timeMs);

    // Getters
    // get view
    const sf::View& getView();
};
