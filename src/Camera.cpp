#include "Camera.hpp"
#include <iostream>

constexpr float viewLerp = 0.015;

// Structors

Camera::Camera(){
    type = gCamera;
}

Camera::~Camera(){}

// Methods
// Smooth movement
void Camera::update(const float& timeMs){
    sf::Vector2f viewPos = view.getCenter();
    const sf::Vector2f& parentPos = parent->getAbsolutePos();

    viewPos += (parentPos - viewPos) * timeMs * viewLerp;
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