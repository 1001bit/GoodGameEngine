#include "GGE/GObjects/GText.hpp"

using gge::GText;

// Structors
GText::GText(){}

GText::~GText(){}

// Methods
// Update text and gobject position
void GText::updatePos(){
    GObject::updatePos();

    text.setPosition(getRect().getPosition());
}; 

// draw self text
void GText::drawSelf(sf::RenderWindow& window){
    window.draw(text);
};