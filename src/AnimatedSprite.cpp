#include "AnimatedSprite.hpp"

// Structors
AnimatedSprite::AnimatedSprite() {
    this->sprite.scale(SPRITE_SCALE, SPRITE_SCALE);

    this->type = gAnimSprite;
    this->elapsedTime = 0;
    this->isFlipped = false;
    this->currentAnimation = nullptr;
}

AnimatedSprite::~AnimatedSprite(){};

// Methods
// add animation to animation map
void AnimatedSprite::insertAnimation(std::string name, const Animation& animation){
    animationMap.insert({name, animation});
}

// start animation
void AnimatedSprite::playAnimation(std::string name){
    if(!animationMap.count(name)){
        return;
    }

    if(currentAnimation != nullptr){
        // if want to play same animation - disallow
        if(currentAnimation == &animationMap.at(name)){
            return;
        }
        // allow playing over looped animations
        if(!currentAnimation->isLooped){
            return;
        }
    }

    elapsedTime = 0;
    currentAnimation = &animationMap.at(name);
    sprite.setTexture(currentAnimation->texture);
    update(0);
}

// update frames, etc
void AnimatedSprite::update(const float& timeMS){
    // no empty animations
    if(currentAnimation == nullptr){
        return;
    }

    // flip
    sf::IntRect currentFrame = getCurrentFrame();
    if(isFlipped){
        currentFrame.left += currentFrame.width;
        currentFrame.width *= -1;
    }

    // set rect
    sprite.setTextureRect(currentFrame);
    if(currentAnimation->playTime == 0){
        return; 
    }

    elapsedTime += timeMS;
    
    // restart or drop frame
    if(elapsedTime >= currentAnimation->playTime){
        elapsedTime -= currentAnimation->playTime;
        if(!currentAnimation->isLooped){
            currentAnimation = nullptr;
        }
    }
}

// update position of sprite
void AnimatedSprite::updateSpritePos(){
    sprite.setPosition(getRect().getPosition());
}

// Getters
// returns sprite
const sf::Sprite& AnimatedSprite::getSprite(){
    return sprite;
}

// returns current frame rect
const sf::IntRect& AnimatedSprite::getCurrentFrame(){
    if(currentAnimation->playTime == 0){
        return currentAnimation->frames[0];
    }
    return currentAnimation->frames[elapsedTime/currentAnimation->frameTime];
}