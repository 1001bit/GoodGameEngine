#include "GGE/GObjects/Body.hpp"

using gge::Body;

// Structors
Body::Body(){
    collidable = 1;
}

Body::~Body(){}

// Getters
// collidable
const bool& Body::isCollidable(){
    return collidable;
}