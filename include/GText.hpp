#pragma once

#include "GObject.hpp"

class GText : public GObject
{
private:
    
public:
    // Structors
    GText();
    ~GText();

    // Variables
    sf::Text text;

    // Methods
    // set text's new position
    void updateDrawablePos();
    // draw self text
    void drawSelf(sf::RenderWindow& window);
};
