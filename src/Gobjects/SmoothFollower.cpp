#include "Gobjects/SmoothFollower.hpp"
#include "GGE/MathHelper.hpp"

using gge::obj::SmoothFollower;

constexpr float FACTOR = 0.98;

// Structors
SmoothFollower::SmoothFollower(){
    this->weighs = 0;
    this->friction = 0;
    this->collidable = 0;
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

    float blend = pow(FACTOR, dTimeMs);
    setCurrentPos(lerp(targetCenterPos, getCurrentRect().getPosition(), blend), true);

    // setCurrentPos(targetCenterPos, true);
}

// set target of following
void SmoothFollower::setTarget(std::shared_ptr<Gobject> newTarget){
    followTargetWeak = newTarget;
};