#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <memory>

constexpr float SPRITE_SCALE = 7;

// All types of objects
enum GObjectType{
    gNone, // done
    gGame, // done
    gSprite, // done
    gAnimSprite, // done
    gPhysBody, // done
    gSolidBody, // done
    gCamera, // done
    gText // TODO
};
// All drawable types of objects
extern std::unordered_set<GObjectType> drawableGObjectTypes;
// All physical types of objects
extern std::unordered_set<GObjectType> bodyGObjectTypes;

// GObject class
class GObject : public std::enable_shared_from_this<GObject>
{
private:
    // Variables
    std::unordered_set<std::shared_ptr<GObject>> children;
    sf::Vector2f relativePos;
    sf::Vector2f absolutePos;
    sf::FloatRect colliderRect;

    // Methods
    void updatePos(); 
    // Add a new child
    void addChild(std::shared_ptr<GObject> newChild);

protected:
    // Variables
    std::shared_ptr<GObject> parent;
    GObjectType type;

    // Methods
    // Set SFML object position after repositioning (if exists)
    virtual void updateSpritePos();

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
    // set collider rect size
    void setColliderSize(float x, float y);

    // Getters
    // Get sprite if it exists
    virtual const sf::Sprite& getSprite();
    // Get position relative to parent's position
    const sf::Vector2f& getRelativePos();
    // Get absolute position of the object
    const sf::Vector2f& getAbsolutePos();
    // Get type of the object
    const GObjectType& getType();
    // Get collider
    const sf::FloatRect& getCollider();
};