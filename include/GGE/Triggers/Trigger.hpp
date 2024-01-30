#pragma once

#include "GGE/GObjects/GObject.hpp"

class Trigger
{
private:
    // Variables
    std::unordered_map<uint16_t, std::weak_ptr<GObject>>* levelGObjectsWId;
    bool active;

    // Methods
    // Do action of trigger if event has happened
    virtual void doAction();

public:
    // Structors
    Trigger();
    ~Trigger();

    // Methods
    // Set vector of gobjecs with id
    void setLevelGObjectsWId(std::unordered_map<uint16_t, std::weak_ptr<GObject>>* newLevelGObjectsWId);
    // tell trigger to check if it's action has happened
    virtual void checkEvent();
};
