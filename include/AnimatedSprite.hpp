#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "GDrawable.hpp"

typedef std::unordered_map<std::string, Animation> anim_map;

class AnimatedSprite : public GDrawable {

private:
    // Variables
    anim_map animationMap;
    Animation* currentAnimation;
    float elapsedTime;

    // Methods
    // Update sprite and gobject pos
    void updatePos(); 

public:
    // Structors
    AnimatedSprite();
    ~AnimatedSprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Start animation with name
    void playAnimation(std::string name);
    // Update the state of current animation
    void update(const float& timeMs);
    // draw self drawable object
    void drawSelf(sf::RenderWindow& window);
    // Add new animation with name
    void insertAnimation(std::string name, const Animation& animation);

    // Getters
    // Get rect of current animation
    const sf::IntRect& getCurrentFrame();
};