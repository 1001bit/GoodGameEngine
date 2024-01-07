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
    const sf::FloatRect& parentRect = parent->getRect();
    sf::Vector2f parentCenterPos(parentRect.left + (parentRect.width / 2), parentRect.top + (parentRect.height / 2));

    viewPos += (parentCenterPos - viewPos) * timeMs * VIEW_LERP;
    view.setCenter(viewPos);
}

// set size of view
void Camera::setSize(float w, float h){
    view.setSize(sf::Vector2f(w, h));
}

// Getters
// get view
const sf::View& Camera::getView(){
    return view;
}