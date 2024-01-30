#include "GGE/Triggers/Trigger.hpp"

// Structors
Trigger::Trigger(){
    active = 1;
}
Trigger::~Trigger(){}

// Methods
// Set vector of gobjecs with id
void Trigger::setLevelGObjectsWId(std::unordered_map<uint16_t, std::weak_ptr<GObject>>* newLevelGObjectsWId){
    levelGObjectsWId = newLevelGObjectsWId;
}
// tell trigger to check if it's action has happened
void Trigger::checkEvent(){}
// Do action of trigger if event has happened
void Trigger::doAction(){}