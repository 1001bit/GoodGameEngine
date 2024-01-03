#include "GObject.hpp"

class PhysBody : public GObject
{
private:
    // Variables
    sf::Vector2f velocity;

    // Methods
    // Control the unit
    virtual void control();
    // Gravity force
    void gravity(const float& timeMs);
public:
    // Structors
    PhysBody();
    ~PhysBody();

    // Methods
    // Update the state
    void update(const float& timeMs);
};
