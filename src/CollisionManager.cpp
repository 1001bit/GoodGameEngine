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
Direction getCollisionDirection(std::shared_ptr<Body> currentBody, std::shared_ptr<Body> obstacleBody){
    if(!obstacleBody->solid){
        return Direction::None;
    }

    ///////////////////////////////////////////////////////////////////////
    // prev rect method (if currentRect in past didn't touch obstacleRect in some direction and now currentRect does, kinematicBody stops in this direction)

    const sf::FloatRect& currentRect = currentBody->getRect();
    const sf::FloatRect& obstacleRect = obstacleBody->getRect();
    const sf::Vector2f& currentBodyVel = currentBody->getVelocity();

    if(!currentRect.intersects(obstacleRect)){
        return Direction::None;
    }
    
    sf::FloatRect prevRect;
    
    // vertical
    prevRect = currentRect;
    prevRect.top -= currentBodyVel.y;
    if(!prevRect.intersects(obstacleRect)){
        // down
        if(currentBodyVel.y > 0){
            return Direction::Down;
        } 
        // up
        else {
            return Direction::Up;
        }
    }

    // horizontal
    prevRect = currentRect;
    prevRect.left -= currentBodyVel.x;
    if(!prevRect.intersects(obstacleRect)){
        // right
        if(currentBodyVel.x > 0){
            return Direction::Right;
        } 
        // left
        else {
            return Direction::Left;
        }
    }

    return Direction::None;
}

// Methods
// Collide all the objects
void CollisionManager::collideAllBodies(){
    for(std::weak_ptr<Body> currentBodyWeak : bodiesSet){
        auto currentBody = currentBodyWeak.lock();
        if(!currentBody){
            continue;
        }

        // don't collide if no collider
        if(currentBody->getRect() == sf::FloatRect()){
            continue;
        }

        // collide body with other body 
        for(std::weak_ptr<Body> obstacleBodyWeak : bodiesSet){
            auto obstacleBody = obstacleBodyWeak.lock();
            if(!obstacleBody){
                continue;
            }
            if(obstacleBody == currentBody || obstacleBody->getRect() == sf::FloatRect()){
                continue;
            }

            currentBody->setCollisionDirection(getCollisionDirection(currentBody, obstacleBody), obstacleBody);
        }
    }
}

// Add new body
void CollisionManager::addNewBody(std::shared_ptr<Body> newBody){
    bodiesSet.push_back(newBody);
}