#include "GGE/Level.hpp"

// Necessary
// GObjects
void Level::initNecessaryGObjects(){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Level
    // camera
    camera = std::make_shared<Camera>();
    camera->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    updatableGObjects.push_back(camera);

    // Gui
    // Dialogue box
    std::shared_ptr<GSprite> dialogueBox = std::make_shared<GSprite>();
    dialogueBox->setNewParent(shared_from_this());
    guiDrawableLayers[0].push_back(dialogueBox);
    
    // Dialogue text
    std::shared_ptr<GText> dialogueText = std::make_shared<GText>();
    dialogueText->setNewParent(dialogueBox);
    guiDrawableLayers[1].push_back(dialogueText);

    dialogueManager.initDrawables(dialogueBox, dialogueText);
};

// All
// Init level
void Level::init(){
    // create layers of drawables
    const int layersCount = 10;
    for(int i = 0; i < layersCount; ++i){
        levelDrawableLayers.push_back(std::vector<std::weak_ptr<GDrawable>>());
        guiDrawableLayers.push_back(std::vector<std::weak_ptr<GDrawable>>());
    }

    // init gui view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);

    // init object
    initNecessaryGObjects();
};