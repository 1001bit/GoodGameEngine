#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <memory>
#include <iostream>
#include "CooldownsManager.hpp"
#include "ControlsManager.hpp"

constexpr float SPRITE_SCALE = 7;

// All types of objects
enum class GObjectType{
    None,
    Body,
    KinematicBody,
};

// 4 directions
enum class Direction {
    None, Up, Down, Right, Left
};


// GObject class
class GObject : public std::enable_shared_from_this<GObject>
{
private:
    // Variables
    sf::Vector2f relativePos;
    sf::FloatRect selfRect;
    bool flipped;
    bool doesFlipMirror;

    // Methods
    // set self rect relative position and children's position
    void updatePos(); 
    // Add a new child
    void addChild(std::shared_ptr<GObject> newChild);

protected:
    // Variables
    std::weak_ptr<GObject> parentWeak;
    std::unordered_set<std::shared_ptr<GObject>> children;
    GObjectType type;
    std::unordered_map<std::string, std::shared_ptr<Cooldown>> selfCooldownMap;

    // Methods
    // Set SFML object position after repositioning (if exists)
    virtual void updateDrawablePos();

public:
    // Structors
    GObject();
    ~GObject();

    // Methods
    // Update the state of the object
    virtual void update(const float& timeMs);
    // Set position relative to parent's position
    void setRelativePos(float x, float y);
    void setRelativePos(const sf::Vector2f& newPos);
    // move self by some distance
    void move(const sf::Vector2f& distance);
    // Set a parent
    void setParent(std::shared_ptr<GObject> newParent);
    // set rect size
    void setRectPixelSize(float x, float y);
    // set the flip of the object
    void setFlip(bool newFlip);
    // set flip ability of the object
    void setDoesFlipMirror(bool newdoesFlipMirror);
    
    // Getters
    // Get position relative to parent's position
    const sf::Vector2f& getRelativePos();
    // Get type of the object
    const GObjectType& getType();
    // Get collider
    const sf::FloatRect& getRect();
    // get flipped
    const bool& isFlipped();
};