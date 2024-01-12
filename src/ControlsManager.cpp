#include "ControlsManager.hpp"

ControlsManager* ControlsManager::instance = nullptr;

// Methods

void ControlsManager::setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap){
    keyboardControlsMap = newControlsMap;
}

void ControlsManager::setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap){
    mouseControlsMap = newControlsMap;
};

bool ControlsManager::isControlHeld(std::string controlId){
    // if there is such keyboard control and it's pressed
    if(keyboardControlsMap.count(controlId) && sf::Keyboard::isKeyPressed(keyboardControlsMap.at(controlId))){
        return 1;
    }
    // if there is such mouse control and it's pressed
    if(mouseControlsMap.count(controlId) && sf::Mouse::isButtonPressed(mouseControlsMap.at(controlId))){
        return 1;
    }
    return 0;
}

bool ControlsManager::isControlPressedOnce(std::string controlId){
    // if there is such keyboard control and it's pressed
    if(keyboardControlsMap.count(controlId) && pressedOnceKeyboardKeys.count(keyboardControlsMap.at(controlId))){
        return 1;
    }
    // if the control wasn't pressed this frame
    if(mouseControlsMap.count(controlId) && pressedOnceMouseButtons.count(mouseControlsMap.at(controlId))){
        return 1;
    }
    return 0;
}

void ControlsManager::changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey){
    if(!keyboardControlsMap.count(controlId)){
        return;
    }
    keyboardControlsMap.at(controlId) = newKey;
}

void ControlsManager::addOncePressedKeyboard(sf::Keyboard::Key controlId){
    pressedOnceKeyboardKeys.insert(controlId);
}

void ControlsManager::addOncePressedMouse(sf::Mouse::Button controlId){
    pressedOnceMouseButtons.insert(controlId);
}

void ControlsManager::clearOncePressed(){
    pressedOnceKeyboardKeys.clear();
    pressedOnceMouseButtons.clear();
}

// Getters

ControlsManager* ControlsManager::getInstance(){
    if (!instance)
        instance = new ControlsManager();
    return instance;
}