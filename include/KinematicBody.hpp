#pragma once

#include "Body.hpp"

// all types of npcs
enum NpcType {
    Walking, // just walking around
    Neutral, // just walking around but fights back
    Hostile // fights when sees you
};

// Class

class KinematicBody : public Body 
{
private:

protected:
    // Variables
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    Direction collisionVerticalDir;
    Direction collisionHorizontalDir;

    // Methods
    // Control the unit
    virtual void control();
    // Gravity force
    virtual void gravity(const float& timeMs);
public:
    // Structors
    KinematicBody();
    ~KinematicBody();

    // Methods
    // choose how to behave collision depending on obstacle
    void collideWith(std::shared_ptr<Body> obstacle);
    // Update the state
    void update(const float& timeMs);
};