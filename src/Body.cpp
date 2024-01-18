#include "Body.hpp"

// Structors
Body::Body(){
    this->type = TBody;
}

Body::~Body(){}

// Methods
// collide seft with obstacle body
void Body::collide(std::shared_ptr<Body> obstacle){};