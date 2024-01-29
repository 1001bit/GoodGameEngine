#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_set>

class ControlsManager
{
private:
    // Singleton
    static ControlsManager* instance;
    ControlsManager() {};

    // Keyboard
    // Controls
    std::unordered_map<std::string, sf::Keyboard::Key> keyboardControlsMap;
    // Pressed once controls
    std::unordered_set<sf::Keyboard::Key> pressedOnceKeyboardKeys;
    // Held controls
    std::unordered_set<sf::Keyboard::Key> heldKeyboardKeys;

    // Mouse
    // Controls
    std::unordered_map<std::string, sf::Mouse::Button> mouseControlsMap;
    // Pressed once controls
    std::unordered_set<sf::Mouse::Button> pressedOnceMouseButtons;
    // Held controls
    std::unordered_set<sf::Mouse::Button> heldMouseButtons;
    
public:
    // Methods
    // Set keyboard controls
    void setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap);
    // Set mouse controls
    void setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap);
    
    // Change keyboard control
    void changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey);

    // Is control held now
    bool isControlHeld(const std::string& controlId);

    // Is control pressed once
    bool isControlPressed(const std::string& controlId);

    // Control press
    void addPressedKeyboard(sf::Keyboard::Key key);
    void addPressedMouse(sf::Mouse::Button button);
    // Clear pressed list
    void clearPressed();

    // Control release
    void keyboardControlRelease(sf::Keyboard::Key key);
    void mouseControlRelease(sf::Mouse::Button button);

    // Singleton
    static ControlsManager* getInstance();
};