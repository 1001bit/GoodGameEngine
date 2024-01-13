#include "Camera.hpp"

constexpr float VIEW_LERP = 0.02;

// Structors
Camera::Camera(){
    type = TCamera;
}

Camera::~Camera(){}

// Methods
// Smooth movement
void Camera::update(const float& timeMs){
    sf::Vector2f viewPos = view.getCenter();
    const sf::FloatRect& targetRect = followTarget->getRect();
    sf::Vector2f targetCenterPos(targetRect.left + (targetRect.width / 2), targetRect.top + (targetRect.height / 2));

    viewPos += (targetCenterPos - viewPos) * timeMs * VIEW_LERP;
    view.setCenter(viewPos);
}

// set size of view
void Camera::setSize(float w, float h){
    view.setSize(sf::Vector2f(w, h));
}

// set target of following
void Camera::setTarget(std::shared_ptr<GObject> newTarget){
    followTarget = newTarget;
};

// Getters
// get view
const sf::View& Camera::getView(){
    return view;
}