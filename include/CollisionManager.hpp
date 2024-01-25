#pragma once

#include "Body.hpp"
#include <set>

class CollisionManager
{
private:
    // Singleton
    static CollisionManager* instance;
    CollisionManager(){};

    // Variables
    // Bodies set
    std::vector<std::weak_ptr<Body>> bodiesSet;
public:
    // Methods
    // Collide all the objects
    void collideAllBodies(); 
    // Add new body
    void addNewBody(std::shared_ptr<Body> newBody);

    // Singleton
    static CollisionManager* getInstance();
};
