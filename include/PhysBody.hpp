#include "KinematicBody.hpp"

class PhysBody : public KinematicBody
{
private:
    // Methods
    // Gravity force
    void gravity(const float& timeMs);
protected:
    // Methods
    // control the unit
    virtual void control();
public:
    // Structors
    PhysBody();
    ~PhysBody();
};
