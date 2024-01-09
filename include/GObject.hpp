#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <memory>
#include <iostream>

constexpr float SPRITE_SCALE = 7;

// All types of objects
enum GObjectType{
    TNone, // done
    TSprite, // done
    TAnimSprite, // done
    TKinematicBody, // done
    TSolidBody, // done
    TCamera, // done
    TText // TODO
};
// All drawable types of objects
extern const std::unordered_set<GObjectType> DRAWABLE_GOBJECT_TYPES;
// All physical types of objects
extern const std::unordered_set<GObjectType> BODY_GOBJECT_TYPES;


// GObject class
class GObject : public std::enable_shared_from_this<GObject>
{
private:
    // Variables
    std::unordered_set<std::shared_ptr<GObject>> children;
    sf::Vector2f relativePos;
    sf::FloatRect selfRect;

    // Methods
    // update slef position and children
    void updatePos(); 
    // Add a new child
    void addChild(std::shared_ptr<GObject> newChild);

protected:
    // Variables
    std::shared_ptr<GObject> parent;
    GObjectType type;

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
    // recieve collision data 
    virtual void collide(std::shared_ptr<GObject> obstacle);
    // Set position relative to parent's position
    void setRelativePos(float x, float y);
    void setRelativePos(const sf::Vector2f& newPos);
    // Set a parent
    void setParent(std::shared_ptr<GObject> newParent);
    // set rect size
    void setRectSize(float x, float y);

    // Getters
    // Get drawable if it exists
    virtual const sf::Drawable& getDrawable();
    // Get position relative to parent's position
    const sf::Vector2f& getRelativePos();
    // Get type of the object
    const GObjectType& getType();
    // Get collider
    const sf::FloatRect& getRect();
};