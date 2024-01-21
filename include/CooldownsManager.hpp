#pragma once

#include <string>
#include <unordered_map>

struct Cooldown
{
    float currentValue;
    float startValue;
};


class CooldownsManager
{
private:
    // Self instance of singleton
    static CooldownsManager* instance;

    // Variables
    // all the cooldowns
    std::unordered_map<std::string, Cooldown> cooldownsMap;

    // Constructor
    CooldownsManager(){};
public:
    // Methods
    // update all the cooldowns
    void update(const float& timeMs);
    // start cooldown with id
    void startCooldown(std::string cooldownId, unsigned random);
    // set cooldownMap
    void setCooldownsMap(std::unordered_map<std::string, Cooldown> newCooldownsMap);

    // Getters
    // get value of cooldown with id
    float getCooldownCount(std::string cooldownId);
    // get self instance of singletoc
    static CooldownsManager* getInstance();
};