#pragma once

#include "GObject.hpp"

// all types of npcs
enum NpcType {
    Walking, // just walking around
    Neutral, // just walking around but fights back
    Hostile // fights when sees you
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
    std::unordered_map<std::string, float> cooldownMap;
    
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