#include "Camera.hpp"

constexpr float SPEED = 0.03;

// Structors
Camera::Camera(){}

Camera::~Camera(){}

// Methods
// Smooth movement
void Camera::update(const float& dTimeMs){
    auto followTarget = followTargetWeak.lock();

    if(!followTarget){
        return;
    }

    const sf::FloatRect& targetRect = followTarget->getRect();
    sf::Vector2f targetCenterPos(targetRect.left + (targetRect.width / 2), targetRect.top + (targetRect.height / 2));

    move((targetCenterPos - getRelativePos()) * dTimeMs * SPEED);
    // setRelativePos(targetCenterPos);

    view.setCenter(getRelativePos());

    GObject::update(dTimeMs);
}

// set size of view
void Camera::setSize(float w, float h){
    view.setSize(sf::Vector2f(w, h));
}

// set target of following
void Camera::setTarget(std::shared_ptr<GObject> newTarget){
    followTargetWeak = newTarget;
};

// Getters
// get view
const sf::View& Camera::getView(){
    return view;
}