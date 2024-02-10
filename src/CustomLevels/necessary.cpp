#include "inits.hpp"

using namespace gge;

void necessaryInit(std::shared_ptr<Level> level){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Level
    // camera
    level->camera = std::make_shared<Camera>();
    level->camera->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    level->updatableGObjects.push_back(level->camera);

    // Gui
    // Dialogue box
    std::shared_ptr<GSprite> dialogueBox = std::make_shared<GSprite>();
    dialogueBox->setNewParent(level);
    level->guiDrawableLayers[0].push_back(dialogueBox);
    
    // Dialogue text
    std::shared_ptr<GText> dialogueText = std::make_shared<GText>();
    dialogueText->setNewParent(dialogueBox);
    level->guiDrawableLayers[1].push_back(dialogueText);

    level->dialogueManager.initDrawables(dialogueBox, dialogueText);
}