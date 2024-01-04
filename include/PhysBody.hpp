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
    virtual void control(const float& timeMs);
public:
    // Structors
    PhysBody();
    ~PhysBody();
};
