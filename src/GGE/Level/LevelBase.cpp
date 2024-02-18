#include "GGE/Level.hpp"

using gge::Level;

// Structors
Level::Level(){
    // init gui view
    guiView.setRectSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setRelativePos({0, 0});

    // init camera
    camera = std::make_shared<obj::Camera>();
    camera->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    updatableGObjects.push_back(camera);

    // drawables
    drawablesManager.setLayerCount(10);
}

Level::~Level(){
    // clear singleton managers on level delete
    ResourceManager* resourceManager = ResourceManager::getInstance();
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    resourceManager->clear();
    cooldownsManager->clear();
}