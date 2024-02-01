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
protected:
    bool collidable;

public:
    // Structors
    Body();
    ~Body();

    // Getters
    // collidable
    const bool& isCollidable();
};

