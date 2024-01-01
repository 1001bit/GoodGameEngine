#include <SFML/Graphics.hpp>

struct Animation
{
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    float playTime;
    float frameTime;
    bool isLooped;
    Animation(std::string textureName, int frameWidth, float playTime, bool isLooped);
    Animation();
};