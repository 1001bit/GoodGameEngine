#pragma once

#include <SFML/Graphics.hpp>
#include "GDrawable.hpp"

namespace gge {

class GSprite : public GDrawable
{
private:
    // Methods
    // Update sprite and gobject pos
    void updatePos(); 

public:
    // Structors
    GSprite();
    ~GSprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Set a texture
    void setTexture(const sf::Texture& newTexture);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // set the flip of the object
    void setFlip(bool newFlip);
};

}