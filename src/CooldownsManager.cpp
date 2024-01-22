#include "CooldownsManager.hpp"

CooldownsManager* CooldownsManager::instance = nullptr;

// Methods
// update all the cooldowns
void CooldownsManager::updateCooldowns(const float& timeMs){
    for(std::shared_ptr<Cooldown> cooldown : cooldownsSet){
        cooldown->update(timeMs);
    }
};

// get newly created clone of cooldown at id
std::shared_ptr<Cooldown> CooldownsManager::newCooldown(float startValue){
    std::shared_ptr<Cooldown> newCooldown = std::make_shared<Cooldown>(startValue);
    cooldownsSet.insert(newCooldown);
    return newCooldown;
};

// get instance of singleton
CooldownsManager* CooldownsManager::getInstance(){
    if (!instance)
        instance = new CooldownsManager();
    return instance;
}
