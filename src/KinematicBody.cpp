#include "KinematicBody.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
KinematicBody::KinematicBody(){
    this->type = GObjectType::KinematicBody;
}

KinematicBody::~KinematicBody(){}

// Methods
void KinematicBody::gravity(const float& timeMs){};
void KinematicBody::control(){};

// update the state
void KinematicBody::update(const float& timeMs){
    control();
    gravity(timeMs);

    velocity += acceleration * ACCEL_COEFF * timeMs;

    move(velocity);

    // nullify all
    acceleration = sf::Vector2f();
    collisionVerticalDir = Direction::None;
    collisionHorizontalDir = Direction::None;
}

// choose how to behave collision depending on obstacle
void KinematicBody::collideWith(std::shared_ptr<Body> obstacle){
    switch (obstacle->getType())
    {
    case GObjectType::Body:
        break;
    default:
        return;
    }

    ///////////////////////////////////////////////////////////////////////
    // prev rect method (if selfRect in past didn't touch obstacleRect in some direction and now selfRect does, kinematicBody stops in this direction)

    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacle->getRect();

    if(!selfRect.intersects(obstacleRect)){
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
            collisionVerticalDir = Direction::Down;
        } 
        // top
        else {
            setRelativePos(selfRect.left, obstacleRect.top + obstacleRect.height);
            collisionVerticalDir = Direction::Up;
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
            collisionHorizontalDir = Direction::Right;
        } 
        // left
        else {
            setRelativePos(obstacleRect.left + obstacleRect.width, selfRect.top);
            collisionHorizontalDir = Direction::Left;
        }
        velocity.x = 0;
    }
}