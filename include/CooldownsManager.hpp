#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Cooldown.hpp"

class CooldownsManager
{
private:
    // Self instance of singleton
    static CooldownsManager* instance;

    // Variables
    // all the cooldowns clones
    std::unordered_set<std::shared_ptr<Cooldown>> cooldownsSet;

    // Constructor
    CooldownsManager(){};
public:
    // Methods
    // update all the cooldowns
    void updateCooldowns(const float& timeMs);
    // get newly created clone of cooldown at id
    std::shared_ptr<Cooldown> newCooldown(float startValue);

    // Getters
    // get self instance of the singleton
    static CooldownsManager* getInstance();
};