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
    sf::Vector2f acceleration;
public:
    // Structors
    Body();
    ~Body();

    // Variables
    bool solid;
    sf::Vector2f velocity;
    CollisionDirection collisionDir;

    // Methods
    // Update the state
    virtual void update(const float& timeMs);
};

