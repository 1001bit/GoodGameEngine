#pragma once

#include "GGE/GObjects/GObject.hpp"

class Trigger
{
private:
    // Variables
    bool active;

    // Methods
    // Do action of trigger if event has happened
    virtual void doAction();

public:
    // Structors
    Trigger();
    ~Trigger();

    // Methods
    // checks if event has happened and does action if yes
    virtual void checkEvent();
};
