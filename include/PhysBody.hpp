#include "GObject.hpp"

class PhysBody : public GObject
{
private:
    // Variables
    sf::Vector2f velocity;

    // Methods
    // Gravity force
    void gravity(const float& timeMs);
protected:
    // Control the unit
    virtual void control();
public:
    // Structors
    PhysBody();
    ~PhysBody();

    // Methods
    // Update the state
    void update(const float& timeMs);
    // collision behaviour
    void collide(std::shared_ptr<GObject> obstacle);
};
