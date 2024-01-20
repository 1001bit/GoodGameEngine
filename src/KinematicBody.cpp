#include "KinematicBody.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
KinematicBody::KinematicBody(){
    this->type = TKinematicBody;
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

    // nullify all
    acceleration = sf::Vector2f();
    collisionVerticalDir = None;
    collisionHorizontalDir = None;

    // manage cooldowns
    for(std::pair<const std::string, float>& cooldown : cooldownMap){
        if(cooldown.second > 0){
            cooldown.second -= timeMs;
        } else if (cooldown.second < 0){
            cooldown.second = 0;
        }
    }
}

// choose how to behave collision depending on obstacle
void KinematicBody::collideWith(std::shared_ptr<Body> obstacle, sf::RenderWindow& window){
    // collidable types of GObjects
    if(!std::unordered_set{TCollisionGrid, TBody}.count(obstacle->getType())){
        return;
    }
    const sf::FloatRect& selfRect = getRect();

    // get overlap of colliding with obstacle
    sf::FloatRect overlap = obstacle->getOverlapWith(selfRect);
    if(overlap == sf::FloatRect()){
        return;
    }

    // draw overlap rect for debug
    #ifdef DRAWCOLLIDER
    sf::RectangleShape visibleOverlap = sf::RectangleShape();
    visibleOverlap.setFillColor(sf::Color(0, 255, 0, 200));
    visibleOverlap.setSize(overlap.getSize());
    visibleOverlap.setPosition(overlap.getPosition());
    window.draw(visibleOverlap);
    #endif

    if(obstacle->getType() == TCollisionGrid){
        std::cout << overlap.width << " " << overlap.height << "\n";
        return;
    }
    ///////////////////////////////////////////////////////////////////////
    // prev rect method (if body in past didn't touch the obstacle in some direction and now it does, it stops in this direction)
    sf::FloatRect prevRect;
    
    // vertical
    prevRect = selfRect;
    prevRect.top -= velocity.y;
    if(!prevRect.intersects(overlap)){
        // bottom
        if(velocity.y > 0){
            setRelativePos(selfRect.left, overlap.top - selfRect.height);
            collisionVerticalDir = Down;
        } 
        // top
        else {
            setRelativePos(selfRect.left, overlap.top + overlap.height);
            collisionVerticalDir = Up;
        }
        velocity.y = 0;
        return;
    }

    // horizontal
    prevRect = selfRect;
    prevRect.left -= velocity.x;
    if(!prevRect.intersects(overlap)){
        // right
        if(velocity.x > 0){
            setRelativePos(overlap.left - selfRect.width, selfRect.top);
            collisionHorizontalDir = Right;
        } 
        // left
        else {
            setRelativePos(overlap.left + overlap.width, selfRect.top);
            collisionHorizontalDir = Left;
        }
        velocity.x = 0;
    }
}