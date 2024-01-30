#include "GGE/Level.hpp"

// Structors
Level::Level(){
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    ResourceManager* resourceManager = ResourceManager::getInstance();

    cooldownsManager->clean();
    resourceManager->clean();
    dialogueManager.setDialogues({});
}

Level::~Level(){}