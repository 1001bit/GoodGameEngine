#pragma once

#include "GObject.hpp"

enum class NpcType {
    Walking, // just walking around
    Neutral, // just walking around but fights back
    Hostile // fights when sees you
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
    Direction collisionVerticalDir;
    Direction collisionHorizontalDir;

    // Methods
    // Update the state
    virtual void update(const float& timeMs);
};

