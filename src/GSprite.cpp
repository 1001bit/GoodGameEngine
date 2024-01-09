#include "GSprite.hpp"

// Structors
GSprite::GSprite(){
    this->sprite.scale(SPRITE_SCALE, SPRITE_SCALE);
    this->type = TSprite;
}

GSprite::~GSprite(){}

// Methods
// update position of sprite
void GSprite::updateDrawablePos(){
    sprite.setPosition(getRect().getPosition());
}

// set a texture
void GSprite::setTexture(const sf::Texture& newTexture){
    sprite.setTexture(newTexture);
}

// Getters
// returns sprite
const sf::Drawable& GSprite::getDrawable(){
    return sprite;
}
