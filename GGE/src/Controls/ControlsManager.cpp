#include "GGE/Controls/ControlsManager.hpp"

using gge::ControlsManager;

// Singleton
ControlsManager* ControlsManager::instance = nullptr;
ControlsManager* ControlsManager::getInstance(){
    if (!instance)
        instance = new ControlsManager();
    return instance;
}

// Methods
// Set Controls map
void ControlsManager::setControlsMap(std::unordered_map<std::string, Control> controlsMap){
    this->controlsMap = controlsMap;
}

// Check if held
bool ControlsManager::isHeld(const std::string& controlId){
    if(!controlsMap.count(controlId)){
        return false;
    }

    for(sf::Keyboard::Key key : controlsMap.at(controlId).keyboard){
        if(activeControls.keyboard.count(key)){
            return activeControls.keyboard.at(key).held;
        }
    }

    for(sf::Mouse::Button button : controlsMap.at(controlId).mouse){
        if(activeControls.mouse.count(button)){
            return activeControls.mouse.at(button).held;
        }
    }

    return false;
}

// check if pressed once
bool ControlsManager::isPressed(const std::string& controlId, bool onlyNow){
    if(!controlsMap.count(controlId)){
        return false;
    }

    for(sf::Keyboard::Key key : controlsMap.at(controlId).keyboard){
        if(activeControls.keyboard.count(key)){
            // if asked to get only current state of control but it's not pressed just now - false
            if(onlyNow && !activeControls.keyboard.at(key).pressedNow){
                return false;
            }

            return true;
        }
    }

    for(sf::Mouse::Button button : controlsMap.at(controlId).mouse){
        if(activeControls.mouse.count(button)){
            // if asked to get only current state of control but it's not pressed just now - false
            if(onlyNow && !activeControls.mouse.at(button).pressedNow){
                return false;
            }

            return true;
        }
    }

    return false;
}

// Change control
void ControlsManager::changeControl(const std::string& controlId, const Control& control){
    if(!controlsMap.count(controlId)){
        return;
    }
    controlsMap.at(controlId) = control;
}

// On control press
void ControlsManager::controlPress(sf::Keyboard::Key key){
    activeControls.keyboard[key] = {true, true, true};
}

void ControlsManager::controlPress(sf::Mouse::Button button){
    activeControls.mouse[button] = {true, true, true};
}

// On control release
void ControlsManager::controlRelease(sf::Keyboard::Key key){
    if(!activeControls.keyboard.count(key)){
        return;
    }
    ControlParameters& params = activeControls.keyboard.at(key);
    params.held = false;
    if(!params.buffered){
        activeControls.keyboard.erase(key);
    }
}

void ControlsManager::controlRelease(sf::Mouse::Button button){
    if(!activeControls.mouse.count(button)){
        return;
    }
    ControlParameters& params = activeControls.mouse.at(button);
    params.held = false;
    if(!params.buffered){
        activeControls.mouse.erase(button);
    }
}

// Clear the vectors of once pressed controls of controls, that were pressed in the past
void ControlsManager::clearPastBuffer(){
    // keyboard
    for(std::pair<const sf::Keyboard::Key, ControlParameters>& pair : activeControls.keyboard){
        pair.second.buffered = false;
    }
    
    // mouse
    for(std::pair<const sf::Mouse::Button, ControlParameters>& pair : activeControls.mouse){
        pair.second.buffered = false;
    }
}

// Set all the buffer controls state to past
void ControlsManager::updateBuffer(){
    // keyboard
    for(std::pair<const sf::Keyboard::Key, ControlParameters>& pair : activeControls.keyboard){
        pair.second.pressedNow = false;
    }
    
    // mouse
    for(std::pair<const sf::Mouse::Button, ControlParameters>& pair : activeControls.mouse){
        pair.second.pressedNow = false;
    }
}