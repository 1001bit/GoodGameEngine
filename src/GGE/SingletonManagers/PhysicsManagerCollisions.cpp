#include "GGE/SingletonManagers/PhysicsManager.hpp"

// Functions
// Collide two objects
void collideKinematicAndSolid(std::shared_ptr<Body> kinematicBody, std::shared_ptr<Body> solidBody){
    // future rect method (if futureRect in touches solidRect, in some direction and now kinematicRect doesn't, kinematicBody stops in this direction)
    const sf::FloatRect& kinematicRect = kinematicBody->getRect();
    const sf::FloatRect& solidRect = solidBody->getRect();
    sf::Vector2f& kinematicBodyVel = kinematicBody->velocity;

    if(kinematicRect.intersects(solidRect)){
        return;
    }
    
    sf::FloatRect futureRect;
    
    // vertical
    futureRect = kinematicRect;
    futureRect.top += kinematicBodyVel.y;
    if(futureRect.intersects(solidRect)){
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
    futureRect = kinematicRect;
    futureRect.left += kinematicBodyVel.x;
    if(futureRect.intersects(solidRect)){
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
void PhysicsManager::applyCollisions(std::shared_ptr<Body> body){
    // if no rect - next one
    if(body->getRect() == sf::FloatRect()){
        return;
    }

    // only kinematic
    if(body->isSolid()){
        return;
    }

    body->collisionDir = {Direction::None, Direction::None};

    // collide body with other body 
    for(std::weak_ptr<Body> otherBodyWeak : bodiesWeakVector){
        auto otherBody = otherBodyWeak.lock();

        // if obstacle body is nil - next one
        if(!otherBody){
            continue;
        }

        // only solid obstacle
        if(!otherBody->isSolid()){
            continue;
        }

        // if obstacle body is current body or no rect - next one
        if(otherBody == body || otherBody->getRect() == sf::FloatRect()){
            continue;
        }

        // actually collide
        collideKinematicAndSolid(body, otherBody);
    }
}