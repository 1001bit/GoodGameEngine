#include "Cooldown.hpp"

// Structors
Cooldown::Cooldown(float newStartValueMs){
    this->currentValueMs = 0;
    this->startValueMs = newStartValueMs;
}
Cooldown::~Cooldown(){}

// Methods
// start count
void Cooldown::start(unsigned randomMs){
    if(currentValueMs > 0){
        return;
    }
    currentValueMs = startValueMs + rand() % randomMs;
};

// set count to 0
void Cooldown::stop(){
    currentValueMs = 0;
};

// update cooldown value
void Cooldown::update(const float& timeMs){
    if(currentValueMs == 0){
        return;
    }
    currentValueMs -= timeMs;
    if(currentValueMs < 0){
        currentValueMs = 0;
    }
};

// Getters
// get currentValueMs
const float& Cooldown::getCurrentValueMs(){
    return currentValueMs;
};
