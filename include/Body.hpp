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
    // collide seft with obstacle body
    virtual void collide(std::shared_ptr<Body> obstacle);
};

