#include "GText.hpp"

// Structors
GText::GText(){
    this->type = TText;
}

GText::~GText(){}

// Methods

void GText::updateDrawablePos(){
    text.setPosition(getRect().getPosition());
}

// draw self sprite
void GText::drawSelf(sf::RenderWindow& window){
    window.draw(text);
};