#include "Body.hpp"

// Structors
Body::Body(){
    this->type = TBody;
}

Body::~Body(){}

// Methods
// collide seft with obstacle body
void Body::collideWith(std::shared_ptr<Body> obstacle, sf::RenderWindow& window){};
// collide self with obstacle body
sf::FloatRect Body::getOverlapWith(const sf::FloatRect& otherRect){
    const sf::FloatRect& selfRect = getRect();
    sf::FloatRect overlap;
    selfRect.intersects(otherRect, overlap);
    return overlap;
};