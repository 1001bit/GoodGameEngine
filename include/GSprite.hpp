#pragma once

#include <SFML/Graphics.hpp>
#include "GObject.hpp"

class GSprite : public GObject
{
private:

public:
    // Structors
    GSprite();
    ~GSprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Move sprite after self reposition
    void updateDrawablePos();
    // Set a texture
    void setTexture(const sf::Texture& newTexture);

    // Getters
    // get sprite
    const sf::Drawable& getDrawable();
};