#include "Camera.hpp"

constexpr float VIEW_LERP = 0.015;

// Structors

Camera::Camera(){
    type = gCamera;
}

Camera::~Camera(){}

// Methods
// Smooth movement
void Camera::update(const float& timeMs){
    sf::Vector2f viewPos = view.getCenter();
    const sf::Vector2f& parentPos = parent->getRect().getPosition();

    viewPos += (parentPos - viewPos) * timeMs * VIEW_LERP;
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