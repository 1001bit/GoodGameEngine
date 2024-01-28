#include "GText.hpp"

// Structors
GText::GText(){}

GText::~GText(){}

// Methods
// Update text and gobject pos
void GText::updatePos(){
    GObject::updatePos();
    text.setPosition(getRect().getPosition());
}; 

// draw self sprite
void GText::drawSelf(sf::RenderWindow& window){
    window.draw(text);
};