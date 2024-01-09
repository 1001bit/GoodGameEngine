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

// Getters
const sf::Drawable& GText::getDrawable(){
    return text;
}