#include "GGE/SingletonManagers/CooldownsManager.hpp"

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
    for(auto it = cooldownsWeakVector.begin(); it != cooldownsWeakVector.end();){
        std::shared_ptr<Cooldown> cooldown = it->lock();
        if(!cooldown){
            it = cooldownsWeakVector.erase(it);
            continue;
        }
        cooldown->update(dTimeMs);
        ++it;
    }
};

// get newly created clone of cooldown at id
std::shared_ptr<Cooldown> CooldownsManager::newCooldown(float startValue){
    std::shared_ptr<Cooldown> newCooldown = std::make_shared<Cooldown>(startValue);
    cooldownsWeakVector.push_back(newCooldown);
    return newCooldown;
};