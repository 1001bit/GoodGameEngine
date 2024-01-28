#include "CooldownsManager.hpp"

// Singleton
CooldownsManager* CooldownsManager::instance = nullptr;
CooldownsManager* CooldownsManager::getInstance(){
    if (!instance)
        instance = new CooldownsManager();
    return instance;
}


// Methods
// update all the cooldowns
void CooldownsManager::updateCooldowns(const float& dTimeMs){
    for(std::shared_ptr<Cooldown> cooldown : cooldownsSet){
        cooldown->update(dTimeMs);
    }
};

// get newly created clone of cooldown at id
std::shared_ptr<Cooldown> CooldownsManager::newCooldown(float startValue){
    std::shared_ptr<Cooldown> newCooldown = std::make_shared<Cooldown>(startValue);
    cooldownsSet.insert(newCooldown);
    return newCooldown;
};
