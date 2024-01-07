#pragma once

#include "GObject.hpp"

// all types of npcs
enum NpcType {
    Hostile, Neutral, Pacifist
};

// 4 directions
enum Direction {
    None, Top, Bottom, Right, Left
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
    Direction collisionVerticalDir;
    Direction collisionHorizontalDir;
    
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