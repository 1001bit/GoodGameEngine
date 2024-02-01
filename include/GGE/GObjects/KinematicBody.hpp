#pragma once

#include "Body.hpp"

class KinematicBody : public Body
{
private:
    // Rects for interpolation
    sf::FloatRect currentRect;
    sf::FloatRect previousRect;

protected:
    // Variables
    bool weighs;

public:
    // Methods
    // Control the body
    virtual void control();
    // Accelerate the body
    void accelerate(float accelX, float accelY);
    // Interpolate gobject::rect between currentRect and previousRect
    void interpolate(float alpha);
    // Set the position of the current rect
    void setCurrentPosition(sf::Vector2f newPosition);
    // Move the current rect
    void moveCurrentRect(sf::Vector2f moveDistance);

    // Variables
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    CollisionDirection collisionDir;

    // Getters
    // weighs
    const bool& doesWeigh();
    // acceleration
    const sf::Vector2f& getAcceleration();
    // currentRect
    const sf::FloatRect& getCurrentRect();

    // Structors
    KinematicBody();
    ~KinematicBody();
};
