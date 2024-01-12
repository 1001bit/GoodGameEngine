#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_set>

class ControlsManager
{
private:
    // Variables
    // self singleton
    static ControlsManager* instance;

    // all the controls of keyboard
    std::unordered_map<std::string, sf::Keyboard::Key> keyboardControlsMap;
    // all the buttons that were pressed only this frame
    std::unordered_set<sf::Keyboard::Key> pressedOnceKeyboardKeys;

    // all the controls of mouse
    std::unordered_map<std::string, sf::Mouse::Button> mouseControlsMap;
    // all the buttons that were pressed only this frame
    std::unordered_set<sf::Mouse::Button> pressedOnceMouseButtons;

    // Constructor
    ControlsManager() {};
    
public:
    // Methods
    // set new keyboard controls
    void setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap);

    // set new mouse controls
    void setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap);

    // change control
    void changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey);

    // returns true if key is pressed on the moment of call
    bool isControlHeld(std::string controlId);

    // returns true if key is pressed and wasn't pressed until last unheld (single atomic press)
    bool isControlPressedOnce(std::string controlId);

    // add keyboard key that was pressed this frame
    void addOncePressedKeyboard(sf::Keyboard::Key controlId);

    // add mouse button that was pressed this frame
    void addOncePressedMouse(sf::Mouse::Button controlId);

    // update the state. Clear pressed once keys
    void clearOncePressed();

    // Getters
    // get instance
    static ControlsManager* getInstance();
};