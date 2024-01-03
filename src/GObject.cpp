#include "GObject.hpp"

// All drawable types of objects
std::unordered_set<GObjectType> drawableGObjectTypes{
    gAnimSprite, gSprite
};

// Structors

GObject::GObject(){
    this->type = gNone;
}

GObject::~GObject(){}

// Methods
// Virtuals
void GObject::update(const float& timeMs){}
void GObject::updateSpritePos(){}
void GObject::collide(collisionDirection direction){};

// Main

void GObject::setParent(std::shared_ptr<GObject> newParent){
    this->parent = newParent;
    std::shared_ptr<GObject> sharedThis = shared_from_this(); 
    parent->addChild(sharedThis);
}

void GObject::updatePos(){
    if(!parent){
        return;
    }
    absolutePos = parent->getAbsolutePos() + relativePos;
    updateSpritePos();
    for(std::shared_ptr<GObject> child : children) {
        child->updatePos();
    }
}

void GObject::addChild(std::shared_ptr<GObject> newChild){
    children.insert(newChild);
    newChild->updatePos();
}

void GObject::setRelativePos(float x, float y){
    relativePos = sf::Vector2f(x, y);
    updatePos();
}

void GObject::setRelativePos(sf::Vector2f newPos){
    relativePos = newPos;
    updatePos();
}

// Getters

const sf::Sprite& GObject::getSprite(){
    static sf::Sprite dummySprite;
    return dummySprite;
}

const sf::Vector2f& GObject::getAbsolutePos(){
    return absolutePos;
}

const sf::Vector2f& GObject::getRelativePos(){
    return relativePos;
}

const GObjectType& GObject::getType(){
    return type;
}