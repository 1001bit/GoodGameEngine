#include "Collider.hpp"

// Structors
Collider::Collider(){
    this->type = gCollider;
}

Collider::~Collider(){}

// Methods
// Collide with object and tell parent
void Collider::collideWith(std::shared_ptr<Collider> obstacle){

}
// update collider position after move
void Collider::updateSpritePos(){
    setRectPosition(getAbsolutePos());
}