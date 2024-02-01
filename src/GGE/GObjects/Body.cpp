#include "GGE/GObjects/Body.hpp"

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