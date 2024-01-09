#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "GObject.hpp"

typedef std::unordered_map<std::string, Animation> animMap;

class AnimatedSprite : public GObject {

private:
    // Variables
    animMap animationMap;
    Animation* currentAnimation;
    float elapsedTime;

public:
    // Structors
    AnimatedSprite();
    ~AnimatedSprite();

    // Variables
    sf::Sprite sprite;
    bool isFlipped;

    // Methods
    // Start animation with name
    void playAnimation(std::string name);
    // Update the state of current animation
    void update(const float& timeMs);
    // Move sprite after self reposition
    void updateDrawablePos();
    // Add new animation with name
    void insertAnimation(std::string name, const Animation& animation);

    // Getters
    // Get rect of current animation
    const sf::IntRect& getCurrentFrame();
    // get sprite
    const sf::Drawable& getDrawable();
};