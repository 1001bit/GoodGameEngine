#include "GGE/GObjects/Camera.hpp"

constexpr float FACTOR = 0.98;

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f) {
    return (a * (1.f - f)) + (b * f);
}

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
    sf::Vector2f targetCenterPos(targetRect.getPosition() + targetRect.getSize()/2.f);
    sf::Vector2f cameraRectNewPos(targetCenterPos - getRect().getSize()/2.f);

    float blend = pow(FACTOR, dTimeMs);
    setRelativePos(lerp(cameraRectNewPos, getRelativePos(), blend));
    // setRelativePos(cameraRectNewPos);

    view.setCenter(getRelativePos() + getRect().getSize()/2.f);
}

// set size of view
void Camera::setSize(float w, float h){
    view.setSize({w, h});
    setRectSize(w, h);
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