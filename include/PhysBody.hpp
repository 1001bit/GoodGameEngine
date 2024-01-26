#pragma once

#include "Body.hpp"

class PhysBody : public Body
{
private:
    // Methods
    // Gravity force
    void gravity(const float& timeMs);
protected:

public:
    // Methods
    // update state
    virtual void update(const float& timeMs);

    // Structors
    PhysBody();
    ~PhysBody();
};
