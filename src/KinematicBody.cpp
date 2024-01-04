#include "KinematicBody.hpp"

// Functions
// get overlap between two rects
sf::FloatRect getCollisionOverlap(const sf::FloatRect& a, const sf::FloatRect& b){
    sf::FloatRect overlap;
    a.intersects(b, overlap);
    return overlap;
}

// Variables
// all the controls
std::unordered_map<std::string, sf::Keyboard::Key> movementControlsMap{
    {"wLeft", sf::Keyboard::A},
    {"wRight", sf::Keyboard::D},
    {"jump", sf::Keyboard::Space}
};

// Structors
KinematicBody::KinematicBody(){
    this->type = gKinematicBody;
}

KinematicBody::~KinematicBody(){}

// Methods
void KinematicBody::gravity(const float& timeMs){};
void KinematicBody::control(const float& timeMs){};

// update the statement
void KinematicBody::update(const float& timeMs){
    control(timeMs);
    gravity(timeMs);
    setRelativePos(getRelativePos() + velocity);
    collisionVerticalDir = none;
}

// behaviour on collide
void KinematicBody::collide(std::shared_ptr<GObject> obstacle){
    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacle->getRect();
    // only solid body can stop physics body | no collision if no collision!
    if(obstacle->getType() != gSolidBody || !(selfRect.intersects(obstacleRect))){
        return;
    }

    sf::FloatRect overlap = getCollisionOverlap(selfRect, obstacleRect);

    // Horizontal 
    if(overlap.width < overlap.height){
        // right
        if(selfRect.left < obstacleRect.left){
            setRelativePos(obstacleRect.left-selfRect.width, selfRect.top);
            collisionHorizontalDir = right;
        }
        // left
        else {
            setRelativePos(obstacleRect.left + obstacleRect.width, selfRect.top);
            collisionHorizontalDir = left;
        }
        velocity.x = 0;
    } 
    // Vertical
    else {
        // bottom
        if(selfRect.top < obstacleRect.top){
            setRelativePos(selfRect.left, obstacleRect.top - selfRect.height);
            collisionVerticalDir = bottom;
        } 
        // top
        else {
            setRelativePos(selfRect.left, obstacleRect.top + obstacleRect.height);
            collisionVerticalDir = top;
        }
        velocity.y = 0;
    }
}