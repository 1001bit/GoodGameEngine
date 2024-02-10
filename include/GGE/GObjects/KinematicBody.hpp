#pragma once

#include "Body.hpp"

namespace gge {

struct CollisionDirection {
    Direction vertical;
    Direction horizontal;
};

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

    // Structors
    KinematicBody();
    ~KinematicBody();
};

}