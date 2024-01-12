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

// behaviour on collide
void KinematicBody::collide(std::shared_ptr<GObject> obstacle){
    // only solid body can stop physics body
    if(obstacle->getType() != TSolidBody){
        return;
    }

    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacle->getRect();

    // prevRect collision method
    // no collision if no collision!
    if(!(selfRect.intersects(obstacleRect))){
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
            collisionVerticalDir = Down;
        } 
        // top
        else {
            setRelativePos(selfRect.left, obstacleRect.top + obstacleRect.height);
            collisionVerticalDir = Up;
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
            setRelativePos(obstacleRect.left - selfRect.width, selfRect.top);
            collisionHorizontalDir = Right;
        } 
        // left
        else {
            setRelativePos(obstacleRect.left + obstacleRect.width, selfRect.top);
            collisionHorizontalDir = Left;
        }
        velocity.x = 0;
    }
}