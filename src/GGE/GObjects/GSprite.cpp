#include "GGE/GObjects/GSprite.hpp"

using gge::GSprite;

// Structors
GSprite::GSprite(){
    this->sprite.scale(SPRITE_SCALE, SPRITE_SCALE);
}

GSprite::~GSprite(){}

// Methods
// set a texture
void GSprite::setTexture(const sf::Texture& newTexture){
    sprite.setTexture(newTexture);
    setRectSize(sprite.getGlobalBounds().getSize().x, sprite.getGlobalBounds().getSize().y);
}

// set the flip of the object
void GSprite::setFlip(bool newFlip){
    const int textureWidth = sprite.getTexture()->getSize().x;
    const int textureHeight = sprite.getTexture()->getSize().y;

    if(newFlip){
        sprite.setTextureRect(sf::IntRect(textureWidth, 0, -textureWidth, textureHeight));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));
    }

    GObject::setFlip(newFlip);
};

// Update sprite and gobject pos
void GSprite::updatePos(){
    GObject::updatePos();
    sprite.setPosition(getRect().getPosition());
} 

// draw self drawable object
void GSprite::drawSelf(sf::RenderWindow& window){
    window.draw(sprite);
};