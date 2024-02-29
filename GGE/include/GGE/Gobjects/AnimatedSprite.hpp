#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Drawable.hpp"

typedef std::unordered_map<std::string, Animation> anim_map;

namespace gge::obj {

class AnimatedSprite : public Drawable {

private:
    anim_map animationMap;
    Animation* currentAnimation;
    float elapsedTime;

    // Methods
    // Update sprite and gobject pos
    void updatePos(); 

public:
    sf::Sprite sprite;

    // Structors
    AnimatedSprite();
    ~AnimatedSprite();

    // Methods
    // Start animation with name
    void playAnimation(std::string name);
    // Update the state of current animation
    void update(const float& dTimeMs);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // Add new animation with name
    void insertAnimation(std::string name, const Animation& animation);

    // Getters
    // Get rect of current frame of the current animation
    const sf::IntRect& getCurrentFrame();
};

}