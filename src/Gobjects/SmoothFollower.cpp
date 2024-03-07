#include "Gobjects/SmoothFollower.hpp"
#include "GGE/MathHelper.hpp"

using gge::obj::SmoothFollower;

const float SmoothFollower::APPROACH_FACTOR = 0.98;

// Structors
SmoothFollower::SmoothFollower(){
    applyGravity = false;
    applyFriction = false;
    applyCollisions = false;
}
SmoothFollower::~SmoothFollower(){}

// Methods
// Smooth movement
void SmoothFollower::update(const float& dTimeMs){
    auto followTarget = followTargetWeak.lock();

    if(!followTarget){
        return;
    }

    const sf::FloatRect& targetRect = followTarget->getRect();
    sf::Vector2f targetCenterPos(targetRect.getPosition() + targetRect.getSize()/2.f);

    float blend = pow(APPROACH_FACTOR, dTimeMs);
    setCurrentPos(lerp(targetCenterPos, getCurrentRect().getPosition(), blend), true);

    // setCurrentPos(targetCenterPos, true);
}

// set target of following
void SmoothFollower::setTarget(std::shared_ptr<Gobject> newTarget){
    followTargetWeak = newTarget;
};