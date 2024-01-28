#pragma once

#include "GDrawable.hpp"

class GText : public GDrawable
{
private:
    // Methods
    // Update text and gobject pos
    void updatePos(); 

public:
    // Structors
    GText();
    ~GText();

    // Variables
    sf::Text text;

    // Methods
    // draw self text
    void drawSelf(sf::RenderWindow& window);
};
