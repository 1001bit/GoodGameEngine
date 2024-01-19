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

// collide with base body (solid)
void KinematicBody::collideWithSolidBody(std::shared_ptr<Body> obstacle){
    // prevRect collision method

    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacle->getRect();

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
};

// collide with collision grid (solid)
void KinematicBody::collideWithCollisionGrid(std::shared_ptr<Body> obstacle){
    
};

// choose how to behave collision depending on obstacle
void KinematicBody::collideWith(std::shared_ptr<Body> obstacle){
    switch (obstacle->getType())
    {
    case TBody:
        collideWithSolidBody(obstacle);
        break;
    case TCollisionGrid:
        collideWithCollisionGrid(obstacle);
        break;
    default:
        break;
    }
}