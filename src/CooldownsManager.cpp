#include "CooldownsManager.hpp"

CooldownsManager* CooldownsManager::instance = nullptr;

// Methods
// update all the cooldowns
void CooldownsManager::update(const float& timeMs){
    for(std::pair<const std::string, Cooldown>& cooldown : cooldownsMap){
        float& cooldownValue = cooldown.second.currentValue; 
        if(cooldownValue == 0){
            continue;
        }
        cooldownValue -= timeMs;
        if(cooldownValue < 0){
            cooldownValue = 0;
        }
    }
};

// start cooldown with id
void CooldownsManager::startCooldown(std::string cooldownId, unsigned random){
    if(!cooldownsMap.count(cooldownId)){
        return;
    }
    // set cooldown to it's start value + random value
    cooldownsMap.at(cooldownId).currentValue = cooldownsMap.at(cooldownId).startValue + rand() % random;
};

// set cooldownMap
void CooldownsManager::setCooldownsMap(std::unordered_map<std::string, Cooldown> newCooldownsMap){
    cooldownsMap = newCooldownsMap;
};

// Getters
// get value of cooldown with id
float CooldownsManager::getCooldownCount(std::string cooldownId){
    if(!cooldownsMap.count(cooldownId)){
        return 0;
    }
    return cooldownsMap.at(cooldownId).currentValue;
};

// get instance of singleton
CooldownsManager* CooldownsManager::getInstance(){
    if (!instance)
        instance = new CooldownsManager();
    return instance;
}
