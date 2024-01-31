#include "GGE/Triggers/Trigger.hpp"

// Structors
Trigger::Trigger(){
    active = 1;
}
Trigger::~Trigger(){}

// Methods
// checks if event has happened and does action if yes
void Trigger::checkEvent(){
    if(active){
        doAction();
    }
}
// Do action of trigger if event has happened
void Trigger::doAction(){}