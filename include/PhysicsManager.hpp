#pragma once

#include "Body.hpp"
#include <set>

class PhysicsManager
{
private:
    // Singleton
    static PhysicsManager* instance;
    PhysicsManager(){};

    // Variables
    // Bodies set
    std::vector<std::weak_ptr<Body>> bodiesWeakSet;
public:
    // Methods
    // Manage collisions of all the bodies with each others
    void collideAllBodies(); 
    // Apply gravity on all weigh objects
    void applyGravity(const float& timeMs);
    // Apply the velocities of the bodies
    void applyBodiesVelocity();
    // Apply the friction so body doesn't move for eternity
    void applyFrictionTo(std::shared_ptr<Body> body);
    // Add new body
    void addNewBody(std::shared_ptr<Body> newBody);

    // Singleton
    static PhysicsManager* getInstance();
};
