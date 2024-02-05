#include "GGE/Triggers/TriggersManager.hpp"

// Structors
TriggersManager::TriggersManager(){}
TriggersManager::~TriggersManager(){}

// Methods
// Check all the triggers if their event has happened
void TriggersManager::update(){
    for(auto it = triggersWeakVector.begin(); it != triggersWeakVector.end();){
        auto trigger = it->lock();

        if(!trigger){
            it = triggersWeakVector.erase(it);
            continue;
        }

        trigger->checkEvent();

        ++it;
    }
}

// Add new trigger
void TriggersManager::addNewTrigger(std::shared_ptr<Trigger> newTrigger){
    triggersWeakVector.push_back(newTrigger);
}