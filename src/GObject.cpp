#include "GObject.hpp"

// All drawable types of objects
const std::unordered_set<GObjectType> DRAWABLE_GOBJECT_TYPES{
    TAnimSprite,
    TSprite,
    TText
};

// GObjects that are bodies
const std::unordered_set<GObjectType> BODY_GOBJECT_TYPES{
    TKinematicBody,
    TSolidBody
};

// Structors

GObject::GObject(){
    this->type = TNone;
}

GObject::~GObject(){
    std::cout << "destroyed " << getType() << "\n";
}

// Methods
// Virtuals
void GObject::update(const float& timeMs){}
void GObject::updateDrawablePos(){}
void GObject::collide(std::shared_ptr<GObject> obstacle){};
void GObject::drawSelf(sf::RenderWindow& window){};

// Main

void GObject::setParent(std::shared_ptr<GObject> newParent){
    this->parentWeak = newParent;
    newParent->addChild(shared_from_this());
}

void GObject::updatePos(){
    // locking parent so it's shared ptr
    if(auto parent = parentWeak.lock()){
        selfRect.left = parent->getRect().left + relativePos.x;
        selfRect.top = parent->getRect().top + relativePos.y;
        updateDrawablePos();
        for(std::shared_ptr<GObject> child : children) {
            child->updatePos();
        }
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

void GObject::setRelativePos(const sf::Vector2f& newPos){
    relativePos = newPos;
    updatePos();
}

void GObject::setRectSize(float w, float h){
    selfRect.width = w*SPRITE_SCALE;
    selfRect.height = h*SPRITE_SCALE;
}


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