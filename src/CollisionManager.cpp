#include "CollisionManager.hpp"

// Singleton
CollisionManager* CollisionManager::instance = nullptr;
CollisionManager* CollisionManager::getInstance(){
    if(!instance){
        instance = new CollisionManager();
    }
    return instance;
};

// Functions
// Collide two objects
void collideTwoBodies(std::shared_ptr<Body> currentBody, std::shared_ptr<Body> obstacleBody){
    ///////////////////////////////////////////////////////////////////////
    // prev rect method (if currentRect in past didn't touch obstacleRect in some direction and now currentRect does, kinematicBody stops in this direction)

    const sf::FloatRect& currentRect = currentBody->getRect();
    const sf::FloatRect& obstacleRect = obstacleBody->getRect();
    sf::Vector2f& currentBodyVel = currentBody->velocity;

    // if no collision now - return
    if(!currentRect.intersects(obstacleRect)){
        return;
    }

    if(currentBody->solid || !obstacleBody->solid){
        return;
    }
    
    sf::FloatRect prevRect;
    
    // vertical
    prevRect = currentRect;
    prevRect.top -= currentBodyVel.y;
    if(!prevRect.intersects(obstacleRect)){
        // down
        if(currentBodyVel.y > 0){
            currentBody->setRelativePos(currentRect.left, obstacleRect.top - currentRect.height);
            currentBody->collisionVerticalDir = Direction::Down;
        } 
        // up
        else {
            currentBody->setRelativePos(currentRect.left, obstacleRect.top + obstacleRect.height);
            currentBody->collisionVerticalDir = Direction::Up;
        }
        currentBodyVel.y = 0;
        return;
    }

    // horizontal
    prevRect = currentRect;
    prevRect.left -= currentBodyVel.x;
    if(!prevRect.intersects(obstacleRect)){
        // right
        if(currentBodyVel.x > 0){
            currentBody->setRelativePos(obstacleRect.left - currentRect.width, currentRect.top);
            currentBody->collisionHorizontalDir = Direction::Right;
        } 
        // left
        else {
            currentBody->setRelativePos(obstacleRect.left + obstacleRect.width, currentRect.top);
            currentBody->collisionHorizontalDir = Direction::Left;
        }
        currentBodyVel.x = 0;
    }
}

// Methods
// Collide all the objects
void CollisionManager::collideAllBodies(){
    for(std::weak_ptr<Body> currentBodyWeak : bodiesWeakSet){
        auto currentBody = currentBodyWeak.lock();
        if(!currentBody){
            continue;
        }

        // don't collide if no collider
        if(currentBody->getRect() == sf::FloatRect()){
            continue;
        }

        currentBody->collisionVerticalDir = Direction::None;
        currentBody->collisionHorizontalDir = Direction::None;

        // collide body with other body 
        for(std::weak_ptr<Body> obstacleBodyWeak : bodiesWeakSet){
            auto obstacleBody = obstacleBodyWeak.lock();
            if(!obstacleBody){
                continue;
            }
            if(obstacleBody == currentBody || obstacleBody->getRect() == sf::FloatRect()){
                continue;
            }

            collideTwoBodies(currentBody, obstacleBody);
        }
    }
}

// Add new body
void CollisionManager::addNewBody(std::shared_ptr<Body> newBody){
    bodiesWeakSet.push_back(newBody);
}