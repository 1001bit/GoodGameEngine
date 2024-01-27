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
void collideKinematicAndSolid(std::shared_ptr<Body> kinematicBody, std::shared_ptr<Body> solidBody){
    // prev rect method (if kinematicRect in past didn't touch solidRect in some direction and now kinematicRect does, kinematicBody stops in this direction)

    const sf::FloatRect& kinematicRect = kinematicBody->getRect();
    const sf::FloatRect& solidRect = solidBody->getRect();
    sf::Vector2f& kinematicBodyVel = kinematicBody->velocity;

    // if no collision now - return
    if(!kinematicRect.intersects(solidRect)){
        return;
    }
    
    sf::FloatRect prevRect;
    
    // vertical
    prevRect = kinematicRect;
    prevRect.top -= kinematicBodyVel.y;
    if(!prevRect.intersects(solidRect)){
        // down
        if(kinematicBodyVel.y > 0){
            kinematicBody->setRelativePos(kinematicRect.left, solidRect.top - kinematicRect.height);
            kinematicBody->collisionDir.vertical = Direction::Down;
        } 
        // up
        else {
            kinematicBody->setRelativePos(kinematicRect.left, solidRect.top + solidRect.height);
            kinematicBody->collisionDir.vertical = Direction::Up;
        }
        kinematicBodyVel.y = 0;
        return;
    }

    // horizontal
    prevRect = kinematicRect;
    prevRect.left -= kinematicBodyVel.x;
    if(!prevRect.intersects(solidRect)){
        // right
        if(kinematicBodyVel.x > 0){
            kinematicBody->setRelativePos(solidRect.left - kinematicRect.width, kinematicRect.top);
            kinematicBody->collisionDir.horizontal = Direction::Right;
        } 
        // left
        else {
            kinematicBody->setRelativePos(solidRect.left + solidRect.width, kinematicRect.top);
            kinematicBody->collisionDir.horizontal = Direction::Left;
        }
        kinematicBodyVel.x = 0;
    }
}

// Methods
// Collide all the objects
void CollisionManager::collideAllBodies(){
    for(std::weak_ptr<Body> currentBodyWeak : bodiesWeakSet){
        auto currentBody = currentBodyWeak.lock();
        // if current body is nil or no rect
        if(!currentBody || currentBody->getRect() == sf::FloatRect()){
            continue;
        }

        currentBody->collisionDir = {Direction::None, Direction::None};

        // collide body with other body 
        for(std::weak_ptr<Body> obstacleBodyWeak : bodiesWeakSet){
            auto obstacleBody = obstacleBodyWeak.lock();
            // if obstacle body is nil or no rect
            if(!obstacleBody || obstacleBody->getRect() == sf::FloatRect()){
                continue;
            }
            if(obstacleBody == currentBody){
                continue;
            }

            if(!currentBody->solid && obstacleBody->solid){
                collideKinematicAndSolid(currentBody, obstacleBody);
            }
        }
    }
}

// Add new body
void CollisionManager::addNewBody(std::shared_ptr<Body> newBody){
    bodiesWeakSet.push_back(newBody);
}