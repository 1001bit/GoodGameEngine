#include "Body.hpp"

constexpr float ACCEL_COEFF = 0.1;

// Structors
Body::Body(){
    solid = 0;
    collisionHorizontalDir = Direction::None;
    collisionVerticalDir = Direction::None;
}

Body::~Body(){}

// Methods
// Update the state
void Body::update(const float& timeMs){
    GObject::update(timeMs);

    velocity += acceleration * ACCEL_COEFF * timeMs;

    move(velocity);

    // nullify all
    acceleration = sf::Vector2f();
    collisionVerticalDir = Direction::None;
    collisionHorizontalDir = Direction::None;
};

// collide self with obstacle body
void Body::setCollisionDirection(Direction newDirection, std::shared_ptr<Body> obstacleBody){
    const sf::FloatRect& selfRect = getRect();
    const sf::FloatRect& obstacleRect = obstacleBody->getRect();

    if(newDirection == Direction::None){
        return;
    }

    if(newDirection == Direction::Left || newDirection == Direction::Right){
        collisionHorizontalDir = newDirection;
    } else {
        collisionVerticalDir = newDirection;
    }

    if(solid){
        return;
    }

    switch (newDirection)
    {
    case Direction::Up:
        std::cout << "up\n";
        velocity.y = 0;
        setRelativePos(selfRect.left, obstacleRect.top + obstacleRect.height);
        break;
    case Direction::Down:
        std::cout << "down\n";
        velocity.y = 0;
        setRelativePos(selfRect.left, obstacleRect.top - selfRect.height);
        break;
    case Direction::Left:
        std::cout << "left\n";
        velocity.x = 0;
        setRelativePos(obstacleRect.left + obstacleRect.width, selfRect.top);
        break;
    case Direction::Right:
        std::cout << "right\n";        
        velocity.x = 0;
        setRelativePos(obstacleRect.left - selfRect.width, selfRect.top);
        break;
    
    default:
        break;
    }
};

// Getters
// velocity
const sf::Vector2f& Body::getVelocity(){
    return velocity;
};