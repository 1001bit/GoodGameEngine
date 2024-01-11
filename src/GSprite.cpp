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

// draw self drawable object
void GSprite::drawSelf(sf::RenderWindow& window){
    window.draw(sprite);
};