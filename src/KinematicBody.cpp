#include "KinematicBody.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Variables
// all the controls
std::unordered_map<std::string, sf::Keyboard::Key> movementControlsMap{
    {"wLeft", sf::Keyboard::A},
    {"wRight", sf::Keyboard::D},
    {"wUp", sf::Keyboard::W},
    {"wDown", sf::Keyboard::S},
    {"jump", sf::Keyboard::Space}
};

// Structors
KinematicBody::KinematicBody(){
    this->type = gKinematicBody;
}

KinematicBody::~KinematicBody(){}

// Methods
void KinematicBody::gravity(const float& timeMs){};
void KinematicBody::control(){};

// update the statement
void KinematicBody::update(const float& timeMs){
    control();
    gravity(timeMs);

    velocity += acceleration * ACCEL_COEFF * timeMs;

    setRelativePos(getRelativePos() + velocity);

    acceleration = sf::Vector2f();
    collisionVerticalDir = none;
    collisionHorizontalDir = none;
}

// behaviour on collide
void KinematicBody::collide(std::shared_ptr<GObject> obstacle){
    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacle->getRect();

    // no collision if no collision!
    if(!(selfRect.intersects(obstacleRect))){
        return;
    }

    // only solid body can stop physics body
    if(obstacle->getType() != gSolidBody){
        return;
    }

    sf::FloatRect prevRect;
    
    // vertical
    prevRect = selfRect;
    prevRect.top -= velocity.y;
    if(!prevRect.intersects(obstacleRect)){
        // bottom
        if(velocity.y > 0){
            setRelativePos(selfRect.left, obstacleRect.top - selfRect.height);
            collisionVerticalDir = bottom;
        } 
        // top
        else {
            setRelativePos(selfRect.left, obstacleRect.top + obstacleRect.height);
            collisionVerticalDir = top;
        }
        velocity.y = 0;
        return;
    }

    // horizontal
    prevRect = selfRect;
    prevRect.left -= velocity.x;
    if(!prevRect.intersects(obstacleRect)){
        // right
        if(velocity.x > 0){
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
}