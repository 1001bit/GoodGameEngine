#include "GObject.hpp"

class Collider : GObject
{
private:
    // methods
    void updateSpritePos();
    
    // variables
    sf::Rect<float> rect;
    
public:
    // Structors
    Collider();
    ~Collider();

    // Variables

    // Methods
    // Collide with object and tell parent
    void collideWith(std::shared_ptr<Collider> obstacle);
    // set size of the rect
    void setRectSize(const sf::Vector2f& newSize);
    // set position of the rect
    void setRectPosition(const sf::Vector2f& newPos);

    // Getters
    
};