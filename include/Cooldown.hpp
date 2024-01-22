#pragma once

#include <iostream>
#include <cstdlib>

class Cooldown
{
private:
    float currentValueMs;
    float startValueMs;
public:
    // Structors
    Cooldown(float newStartValueMs);
    ~Cooldown();

    // Methods
    // start count
    void start(unsigned randomMs);
    // update cooldown
    void update(const float& timeMs);

    // Getters
    // get currentValueMs
    const float& getCurrentValueMs();
};