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

// Methods
// Do all the physics stuff to all the bodies
void PhysicsManager::updatePhysics(const float& dTimeMs){
    for(auto it = bodiesWeakVector.begin(); it != bodiesWeakVector.end();){
        auto body = it->lock();
        // if current body is nil or no rect
        if(!body){
            it = bodiesWeakVector.erase(it);
            continue;
        }

        if(body->doesWeigh()){
            applyGravityToAccel(body, dTimeMs);
        }
        if(body->isKinematic()){
            body->control();
            applyAccelerationToVel(body, dTimeMs);
            applyCollisions(body);
            applyVelocityToPos(body);
        }

        ++it;
    }
};

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<Body> body, const float& dTimeMs){
    body->accelerate(0, GFORCE * dTimeMs);
};

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<Body> body, const float& dTimeMs){
    body->velocity += body->getAcceleration() * dTimeMs * ACCEL_COEFF;
    body->acceleration = sf::Vector2f();
};

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<Body> body){
    body->move(body->velocity);
    applyFrictionToVel(body);
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

// Add new body to the vector of bodies
void PhysicsManager::addNewBody(std::shared_ptr<Body> newBody){
    bodiesWeakVector.push_back(newBody);
}