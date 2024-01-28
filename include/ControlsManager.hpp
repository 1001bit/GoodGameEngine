#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_set>

class ControlsManager
{
private:
    // Singleton
    static ControlsManager* instance;
    ControlsManager() {};

    // Variables
    // all the controls of keyboard
    std::unordered_map<std::string, sf::Keyboard::Key> keyboardControlsMap;
    // all the buttons that were pressed only this frame
    std::unordered_set<sf::Keyboard::Key> pressedOnceKeyboardKeys;

    // all the controls of mouse
    std::unordered_map<std::string, sf::Mouse::Button> mouseControlsMap;
    // all the buttons that were pressed only this frame
    std::unordered_set<sf::Mouse::Button> pressedOnceMouseButtons;
    
public:
    // Methods
    // set new keyboard controls
    void setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap);
    // set new mouse controls
    void setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap);
    // change control
    void changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey);

    // returns true if key is pressed on the moment of call
    bool isControlHeld(const std::string& controlId);
    // returns true if key is pressed and wasn't pressed until last unheld (single atomic press)
    bool isControlPressedOnce(const std::string& controlId);

    // add keyboard key that was pressed this frame
    void addOncePressedKeyboard(sf::Keyboard::Key key);
    // add mouse button that was pressed this frame
    void addOncePressedMouse(sf::Mouse::Button button);
    // clear pressed once keys set
    void clearOncePressed();

    // Singleton
    static ControlsManager* getInstance();
};