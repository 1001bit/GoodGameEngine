#include "GDrawable.hpp"

// Structors
GDrawable::GDrawable(){
    this->type = TDrawable;
}

GDrawable::~GDrawable(){}

// Methods
// draw self drawable object
void GDrawable::drawSelf(sf::RenderWindow& window){};