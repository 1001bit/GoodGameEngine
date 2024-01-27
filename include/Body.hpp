#pragma once

#include "GObject.hpp"

enum class NpcType {
    Walking, // just walking around
    Neutral, // just walking around but fights back
    Hostile // fights when sees you
};

struct CollisionDirection {
    Direction vertical;
    Direction horizontal;
};

class Body : public GObject
{
private:

protected:
    // Variables
    bool weighs;
    bool solid;

public:

    // Structors
    Body();
    ~Body();

    // Variables
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    CollisionDirection collisionDir;

    // Methods
    // Update the state
    virtual void update(const float& timeMs);
    // Accelerate the body
    void accelerate(float accelX, float accelY);

    // Getters
    // weighs
    const bool& doesWeigh();
    // solid
    const bool& isSolid();
    // acceleration
    const sf::Vector2f& getAcceleration();
};

