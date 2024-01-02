#include "GSprite.hpp"

// Structors

GSprite::GSprite()
{
    this->sprite.scale(spriteScale, spriteScale);
    this->type = gsprite;
}

GSprite::~GSprite(){}

// Methods
// update position of sprite
void GSprite::updateSpritePos(){
    sprite.setPosition(this->getAbsolutePos());
}

// set a texture
void GSprite::setTexture(const sf::String& textureName){
    texture.loadFromFile(textureName);
    sprite.setTexture(texture);
}

// Getters
// returns sprite
const sf::Sprite& GSprite::getSprite(){
    return sprite;
}
