#include "GGE/Gobjects/Body.hpp"

using gge::obj::Body;

// Structors
Body::Body(){
    this->collidable = 1;
}

Body::~Body(){}

// Getters
// collidable
const bool& Body::isCollidable(){
    return collidable;
}