#include "Body.hpp"

// Structors
Body::Body(){
    this->type = TBody;
}

Body::~Body(){}

// Methods
sf::FloatRect Body::getOverlap(const sf::FloatRect& otherRect){
    sf::FloatRect overlap;
    otherRect.intersects(this->getRect(), overlap);
    return overlap;
}