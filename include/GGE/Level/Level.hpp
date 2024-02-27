#pragma once

#include "GGE/Gobjects/Gobject.hpp"

#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Instructions/InstructionsManager.hpp"
#include "GGE/DrawablesManager/DrawablesManager.hpp"
#include "GGE/Cooldowns/CooldownsManager.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"

namespace gge {

class Level : public obj::Gobject
{
private:
    
public:
    bool active;

    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Managers
    InstructionsManager instructionsManager;
    PhysicsManager physicsManager;
    DrawablesManager drawablesManager;
    CooldownsManager cooldownsManager;
    ResourceManager resourceManager;

    // Updatable
    std::vector<std::weak_ptr<obj::Gobject>> updatableGobjects;
    // With own id
    std::unordered_map<ushort, std::weak_ptr<obj::Gobject>> gobjectIdMap;

    // Level view
    std::weak_ptr<obj::View> levelViewWeak;
    // Gui view
    std::weak_ptr<obj::View> guiViewWeak;
    ///////////////////////////

    // Methods
    // Init the level
    void init();
    // Update states of all the objects
    void update(const float& dTimeMs);
};

}