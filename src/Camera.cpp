#include "Camera.hpp"

constexpr float viewLerp = 0.015;

void Camera::smoothViewMovement(sf::View& view, sf::Vector2f followPosition, float time){
    sf::Vector2f viewPos = view.getCenter();
    viewPos += (followPosition - viewPos) * time * viewLerp;
    view.setCenter(viewPos);
}

Camera::Camera()
{
}

Camera::~Camera()
{
}