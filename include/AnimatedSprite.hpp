#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

using std::cout;

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