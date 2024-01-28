#include "GGE/SingletonManagers/PhysicsManager.hpp"

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

// Do all the physics stuff to all the bodies
void PhysicsManager::updatePhysics(const float& dTimeMs){
    for(std::weak_ptr<Body> bodyWeak : bodiesWeakVector){
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
// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<Body> body, const float& dTimeMs){
    if(!body->doesWeigh()){
        return;
    }

    body->accelerate(0, GFORCE * dTimeMs);
};

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<Body> body){
    if(!body->isKinematic()){
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
    bodiesWeakVector.push_back(newBody);
}