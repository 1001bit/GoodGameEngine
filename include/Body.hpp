#pragma once

#include "GObject.hpp"

#define DRAWCOLLIDER

class Body : public GObject
{
private:
    
public:
    // Structors
    Body();
    ~Body();

    // Methods
    // collide self with obstacle body
    virtual void collideWith(std::shared_ptr<Body> obstacle, sf::RenderWindow& window);
    // get overlap of collision of self and other rect
    virtual sf::FloatRect getOverlapWith(const sf::FloatRect& otherRect);
};

