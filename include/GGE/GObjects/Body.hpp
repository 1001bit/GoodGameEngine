#pragma once

#include "GObject.hpp"

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

