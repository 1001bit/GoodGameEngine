#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Cooldown.hpp"

class CooldownsManager
{
private:
    // Self Singleton
    static CooldownsManager* instance;
    CooldownsManager(){};

    // Variables
    // all the cooldowns clones
    std::unordered_set<std::shared_ptr<Cooldown>> cooldownsSet;
    
public:
    // Methods
    // update all the cooldowns
    void updateCooldowns(const float& timeMs);
    // get newly created clone of cooldown at id
    std::shared_ptr<Cooldown> newCooldown(float startValue);

    // Getters
    // get self singleton instance
    static CooldownsManager* getInstance();
};