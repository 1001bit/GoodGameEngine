#include "GSprite.hpp"

// Structors
GSprite::GSprite(){
    this->sprite.scale(SPRITE_SCALE, SPRITE_SCALE);
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
    const int textureWidth = sprite.getTexture()->getSize().x;
    const int textureHeight = sprite.getTexture()->getSize().y;

    if(isFlipped()){
        sprite.setTextureRect(sf::IntRect(textureWidth, 0, -textureWidth, textureHeight));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));
    }
    window.draw(sprite);
};