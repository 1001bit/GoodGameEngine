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
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    Direction collisionVerticalDir;
    Direction collisionHorizontalDir;
public:
    // Structors
    Body();
    ~Body();

    // Variables
    bool solid;

    // Methods
    // Update the state
    virtual void update(const float& timeMs);
    // collide self with obstacle body
    void setCollisionDirection(Direction newDirection, std::shared_ptr<Body> obstacleBody);

    // Getters
    // velocity
    const sf::Vector2f& getVelocity();
};

