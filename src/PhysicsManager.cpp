#include "PhysicsManager.hpp"

constexpr float GFORCE = 0.08;
constexpr float AIR_FRICTION = 0.96;
constexpr float GROUND_FRICTION = 0.6;

// Singleton
PhysicsManager* PhysicsManager::instance = nullptr;
PhysicsManager* PhysicsManager::getInstance(){
    if(!instance){
        instance = new PhysicsManager();
    }
    return instance;
};

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
void PhysicsManager::collideAllBodies(){
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

            if(!currentBody->isSolid() && obstacleBody->isSolid()){
                collideKinematicAndSolid(currentBody, obstacleBody);
            }
        }
    }
}

// Apply gravity on all weigh objects
void PhysicsManager::applyGravity(const float& timeMs){
    for(std::weak_ptr<Body> bodyWeak : bodiesWeakSet){
        auto body = bodyWeak.lock();
        // if current body is nil or no rect
        if(!body || !body->doesWeigh()){
            continue;
        }

        body->accelerate(0, GFORCE * timeMs);
    }
};

// Apply the velocities of the bodies
void PhysicsManager::applyBodiesVelocity(){
    for(std::weak_ptr<Body> bodyWeak : bodiesWeakSet){
        auto body = bodyWeak.lock();
        // if current body is nil or no rect
        if(!body){
            continue;
        }

        body->move(body->velocity);

        applyFrictionTo(body);
    }
};

// Apply the friction so body doesn't move for eternity
void PhysicsManager::applyFrictionTo(std::shared_ptr<Body> body){
    if(body->doesWeigh()){
        if(body->collisionDir.vertical == Direction::Down){
            body->velocity.x *= GROUND_FRICTION;
        } else {
            body->velocity.x *= AIR_FRICTION;
        }
    } else {
        body->velocity.x *= GROUND_FRICTION;
    }
}

// Add new body
void PhysicsManager::addNewBody(std::shared_ptr<Body> newBody){
    bodiesWeakSet.push_back(newBody);
}