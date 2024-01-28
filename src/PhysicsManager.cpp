#include "PhysicsManager.hpp"

constexpr float GFORCE = 0.08;
constexpr float AIR_FRICTION = 0.98;
constexpr float GROUND_FRICTION = 0.7;
constexpr float ACCEL_COEFF = 0.1;

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

// Do all the physics stuff to all the bodies
void PhysicsManager::updatePhysics(const float& dTimeMs){
    for(std::weak_ptr<Body> bodyWeak : bodiesWeakSet){
        auto body = bodyWeak.lock();
        // if current body is nil or no rect
        if(!body){
            continue;
        }

        applyGravityToAccel(body, dTimeMs);
        applyAccelerationToVel(body, dTimeMs);
        applyCollisions(body);
        applyVelocityToPos(body);
    }
};

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
    for(std::weak_ptr<Body> otherBodyWeak : bodiesWeakSet){
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

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<Body> body, const float& dTimeMs){
    if(!body->doesWeigh()){
        return;
    }

    body->accelerate(0, GFORCE * dTimeMs);
};

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<Body> body){
    if(body->isSolid()){
        return;
    }

    body->move(body->velocity);

    applyFrictionToVel(body);
};

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<Body> body, const float& dTimeMs){
    body->velocity += body->getAcceleration() * dTimeMs * ACCEL_COEFF;
    body->acceleration = sf::Vector2f();
};

// Apply the friction so body doesn't move for eternity
void PhysicsManager::applyFrictionToVel(std::shared_ptr<Body> body){
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