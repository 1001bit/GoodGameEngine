#pragma once

#include <SFML/Graphics.hpp>

class Camera
{

private:
    void smoothViewMovement(sf::View& view, sf::Vector2f followPosition, float time);
    
public:
    Camera();
    ~Camera();

};
