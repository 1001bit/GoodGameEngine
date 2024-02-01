#include "GGE/SingletonManagers/PhysicsManager.hpp"

constexpr float GFORCE = 0.08;
constexpr float AIR_FRICTION = 0.98;
constexpr float GROUND_FRICTION = 0.01;
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
    for(auto it = kinematicBodiesWeakVector.begin(); it != kinematicBodiesWeakVector.end();){
        auto kinematicBody = it->lock();
        // if current body is nil or no rect
        if(!kinematicBody){
            it = kinematicBodiesWeakVector.erase(it);
            continue;
        }

        // interpolation
        kinematicBody->previousRect = kinematicBody->currentRect;

        // control body (like player, npc)
        kinematicBody->control();

        if(kinematicBody->doesWeigh()){
            applyGravityToAccel(kinematicBody, dTimeMs);
        }

        applyAccelerationToVel(kinematicBody, dTimeMs);
        if(kinematicBody->isCollidable()){
            applyCollisions(kinematicBody);
        }
        applyVelocityToPos(kinematicBody);
        applyFrictionToVel(kinematicBody);

        ++it;
    }
};

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->accelerate(0, GFORCE * dTimeMs);
};

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->velocity += kinematicBody->acceleration * dTimeMs * ACCEL_COEFF;
    kinematicBody->acceleration = sf::Vector2f();
};

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<KinematicBody> kinematicBody){
    kinematicBody->moveCurrentRect(kinematicBody->velocity);
};

// Apply the friction so body doesn't move for eternity
void PhysicsManager::applyFrictionToVel(std::shared_ptr<KinematicBody> kinematicBody){
    if(kinematicBody->doesWeigh()){
        if(kinematicBody->collisionDir.vertical == Direction::Down){
            kinematicBody->velocity.x *= GROUND_FRICTION;
        } else {
            kinematicBody->velocity.x *= AIR_FRICTION;
        }
    } else {
        kinematicBody->velocity.x *= GROUND_FRICTION;
    }
}

// Interpolate all the kinematic bodies
void PhysicsManager::interpolateKinematics(float alpha){
    for(auto it = kinematicBodiesWeakVector.begin(); it != kinematicBodiesWeakVector.end();){
        auto kinematicBody = it->lock();
        // if current body is nil or no rect
        if(!kinematicBody){
            it = kinematicBodiesWeakVector.erase(it);
            continue;
        }

        sf::FloatRect& currentRect = kinematicBody->currentRect;
        sf::FloatRect& previousRect = kinematicBody->previousRect;
        const sf::FloatRect& rect = kinematicBody->getRect();

        kinematicBody->setRelativePos(currentRect.getPosition() * alpha + previousRect.getPosition() * (1.f - alpha));

        ++it;
    }
};

// Add new body to the vector of solid bodies
void PhysicsManager::addNewSolidBody(std::shared_ptr<Body> newBody){
    solidBodiesWeakVector.push_back(newBody);
}

// Add new body to the vector of kinematic bodies
void PhysicsManager::addNewKinematicBody(std::shared_ptr<KinematicBody> newBody){
    kinematicBodiesWeakVector.push_back(newBody);
}