#pragma once

#include "GObject.hpp"

// 4 directions of possible collisions
enum CollisionDirection {
    none, top, bottom, right, left
};

// all the controls
extern std::unordered_map<std::string, sf::Keyboard::Key> movementControlsMap;

class KinematicBody : public GObject 
{
private:

protected:
    // Variables
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    CollisionDirection collisionVerticalDir;
    CollisionDirection collisionHorizontalDir;
    
    // Methods
    // Control the unit
    virtual void control();
    // Gravity force
    virtual void gravity(const float& timeMs);
public:
    // Structors
    KinematicBody();
    ~KinematicBody();

    // Methods
    // collision behaviour
    void collide(std::shared_ptr<GObject> obstacle);
    // Update the state
    void update(const float& timeMs);
};