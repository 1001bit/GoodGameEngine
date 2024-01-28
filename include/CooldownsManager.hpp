#pragma once

#include <string>
#include <vector>
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
    std::vector<std::shared_ptr<Cooldown>> cooldownsVector;
    
public:
    // Methods
    // update all the cooldowns
    void updateCooldowns(const float& dTimeMs);
    // get newly created clone of cooldown at id
    std::shared_ptr<Cooldown> newCooldown(float startValue);

    // Getters
    // get self singleton instance
    static CooldownsManager* getInstance();
};