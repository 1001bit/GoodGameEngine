#include "Camera.hpp"

constexpr float VIEW_LERP = 0.02;

// Structors
Camera::Camera(){}

Camera::~Camera(){}

// Methods
// Smooth movement
void Camera::update(const float& timeMs){
    auto followTarget = followTargetWeak.lock();

    if(!followTarget){
        return;
    }

    const sf::FloatRect& targetRect = followTarget->getRect();
    sf::Vector2f targetCenterPos(targetRect.left + (targetRect.width / 2), targetRect.top + (targetRect.height / 2));
    
    move((targetCenterPos - getRelativePos()) * timeMs * VIEW_LERP);
    // setRelativePos(targetCenterPos);

    view.setCenter(getRelativePos());
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