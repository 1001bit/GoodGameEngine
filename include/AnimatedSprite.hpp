#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#define TEXTURE_SCALE 7

using std::cout;

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

typedef std::unordered_map<std::string, Animation> animMap;

class AnimatedSprite {

animMap animationMap;
Animation* currentAnimation;
float elapsedTime;

public:
    AnimatedSprite();
    ~AnimatedSprite();

    sf::Sprite sprite;
    bool isFlipped;

    void playAnimation(std::string name);
    void updateAnimation(float dTime);
    void insertAnimation(std::string name, Animation animation);

    const sf::IntRect& getCurrentFrame();
};