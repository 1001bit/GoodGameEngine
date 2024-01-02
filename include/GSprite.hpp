#pragma once

#include <SFML/Graphics.hpp>
#include "GObject.hpp"

class GSprite : public GObject
{
private:
    // Variables
    sf::Texture texture;
public:
    // Structors
    GSprite();
    ~GSprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Move sprite after self reposition
    void updateSpritePos();
    // Set a texture
    void setTexture(const sf::String& textureName);

    // Getters
    // get sprite
    const sf::Sprite& getSprite();
};