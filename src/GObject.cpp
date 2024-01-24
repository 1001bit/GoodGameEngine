#include "GObject.hpp"

// Structors
GObject::GObject(){
    this->type = GObjectType::None;
    this->flipped = 0;
    this->doesFlipMirror = 0;
}

GObject::~GObject(){}

// Methods
// Virtuals
void GObject::update(const float& timeMs){}
void GObject::updateDrawablePos(){}

// Main

void GObject::setParent(std::shared_ptr<GObject> newParent){
    this->parentWeak = newParent;
    newParent->addChild(shared_from_this());
}

void GObject::updatePos(){
    // set self position related to parent's
    if(auto parent = parentWeak.lock()){
        selfRect.left = parent->getRect().left + relativePos.x;
        selfRect.top = parent->getRect().top + relativePos.y;
        updateDrawablePos();

        // update children's position
        for(std::shared_ptr<GObject> child : children) {
            child->updatePos();
        }
    }
}

void GObject::addChild(std::shared_ptr<GObject> newChild){
    children.insert(newChild);
    newChild->updatePos();
}

void GObject::setRelativePos(const sf::Vector2f& newPos){
    relativePos = newPos;
    updatePos();
}

void GObject::setRelativePos(float x, float y){
    setRelativePos(sf::Vector2f(x, y));
}

void GObject::move(const sf::Vector2f& distance){
    setRelativePos(getRelativePos() + distance);
};

void GObject::setRectPixelSize(float w, float h){
    selfRect.width = w*SPRITE_SCALE;
    selfRect.height = h*SPRITE_SCALE;
}

void GObject::setFlip(bool newFlip){
    if(flipped != newFlip && doesFlipMirror){
        setRelativePos(-getRelativePos().x, getRelativePos().y);
    }
    flipped = newFlip;
    for(std::shared_ptr<GObject> child : children) {
        child->setFlip(flipped);
    }
}

void GObject::setDoesFlipMirror(bool newDoesFlipMirror){
    doesFlipMirror = newDoesFlipMirror;
};

// Getters

const sf::Vector2f& GObject::getRelativePos(){
    return relativePos;
}

const GObjectType& GObject::getType(){
    return type;
}

const sf::FloatRect& GObject::getRect(){
    return selfRect;
}

const bool& GObject::isFlipped(){
    return flipped;
};