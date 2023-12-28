#include "AnimatedSprite.hpp"

// animation constructor
Animation::Animation(std::string textureName, int frameWidth, float playTime, bool isLooped){
    this->texture.loadFromFile(textureName);

    // add frames to vector depending on frame width
    for(int x = 0; x < int(this->texture.getSize().x / frameWidth); ++x){
        this->frames.push_back(sf::IntRect(x*frameWidth, 0, frameWidth, this->texture.getSize().y));
    }

    this->playTime = playTime;
    this->frameTime = this->playTime / this->frames.size();
    this->isLooped = isLooped;
}

Animation::Animation(){

}

// animated sprite constructor
AnimatedSprite::AnimatedSprite() {
    this->sprite.setScale(TEXTURE_SCALE, TEXTURE_SCALE);
    this->elapsedTime = 0;
    this->isFlipped = false;
    this->currentAnimation = nullptr;
}

// add animation to map
void AnimatedSprite::insertAnimation(std::string name, Animation animation){
    animationMap.insert({name, animation});
    // Don't know what to do? Just play idle animation
    if(name == "idle"){
        playAnimation(name);
    }
}

// start animation
void AnimatedSprite::playAnimation(std::string name){
    if(!animationMap.count(name)){
        return;
    }

    if(currentAnimation != nullptr){
        if(currentAnimation == &animationMap.at(name)){
            return;
        }
        // every non-looped animation will go into idle whis is looped. So when looped animation is played only then we play another one 
        if(!currentAnimation->isLooped){
            return;
        }
    }

    elapsedTime = 0;
    currentAnimation = &animationMap.at(name);
    sprite.setTexture(currentAnimation->texture);
    updateAnimation(0);
}

// update frames, etc
void AnimatedSprite::updateAnimation(float dTime){
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

    elapsedTime += dTime;
    
    // restart or drop frame
    if(elapsedTime >= currentAnimation->playTime){
        elapsedTime -= currentAnimation->playTime;
        if(!currentAnimation->isLooped){
            currentAnimation = nullptr;
            playAnimation("idle");
        }
    }
}


// GETTERS

// returns current frame rect
const sf::IntRect& AnimatedSprite::getCurrentFrame(){
    if(currentAnimation->playTime == 0){
        return currentAnimation->frames[0];
    }
    return currentAnimation->frames[elapsedTime/currentAnimation->frameTime];
}