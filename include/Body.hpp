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
    virtual sf::FloatRect getOverlap(const sf::FloatRect& otherRect);
};

