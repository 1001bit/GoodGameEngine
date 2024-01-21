#pragma once

#include "GObject.hpp"

class Body : public GObject
{
private:
    
public:
    // Structors
    Body();
    ~Body();

    // Methods
    // collide self with obstacle body
    virtual void collideWith(std::shared_ptr<Body> obstacle);
};
