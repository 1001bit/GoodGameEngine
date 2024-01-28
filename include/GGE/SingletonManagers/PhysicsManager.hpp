#pragma once

#include "GGE/GObjects/Body.hpp"
#include <vector>

class PhysicsManager
{
private:
    // Singleton
    static PhysicsManager* instance;
    PhysicsManager(){};

    // Variables
    // Bodies vector
    std::vector<std::weak_ptr<Body>> bodiesWeakVector;
public:
    // Methods
    // Manage collisions of all the bodies with each others
    void applyCollisions(std::shared_ptr<Body> body); 
    // Apply gravity on all weigh objects
    void applyGravityToAccel(std::shared_ptr<Body> body, const float& dTimeMs);
    // Apply the velocities of the bodies
    void applyVelocityToPos(std::shared_ptr<Body> body);
    // Apply the acceleration to the velocity
    void applyAccelerationToVel(std::shared_ptr<Body> body, const float& dTimeMs);
    // Apply the friction so body doesn't move for eternity
    void applyFrictionToVel(std::shared_ptr<Body> body);
    // Do all the physics stuff to all the bodies
    void updatePhysics(const float& dTimeMs);
    // Add new body
    void addNewBody(std::shared_ptr<Body> newBody);

    // Singleton
    static PhysicsManager* getInstance();
};
