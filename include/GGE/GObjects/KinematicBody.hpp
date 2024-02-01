#pragma once

#include "Body.hpp"

class KinematicBody : public Body
{
private:


protected:
    // Variables
    bool weighs;

public:
    // Methods
    // Control the body
    virtual void control();
    // Accelerate the body
    void accelerate(float accelX, float accelY);
    // Set the position of the current rect
    void setCurrentPosition(sf::Vector2f newPosition);
    // Move the current rect
    void moveCurrentRect(sf::Vector2f moveDistance);
    // set size of current rect
    void setRectSize(float w, float h);

    // Variables
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    CollisionDirection collisionDir;  

    sf::FloatRect currentRect;
    sf::FloatRect previousRect;

    // Getters
    // weighs
    const bool& doesWeigh();
    // acceleration
    const sf::Vector2f& getAcceleration();

    // Structors
    KinematicBody();
    ~KinematicBody();
};