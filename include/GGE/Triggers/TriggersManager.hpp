#pragma once

#include <vector>
#include "GGE/Triggers/Trigger.hpp"

class TriggersManager
{
private:
    std::vector<std::weak_ptr<Trigger>> triggersWeakVector;

public:
    // Structors
    TriggersManager();
    ~TriggersManager();

    // Methods
    // Check all the triggers if their event has happened
    void update();
    // Add new trigger
    void addNewTrigger(std::shared_ptr<Trigger> newTrigger);
};
