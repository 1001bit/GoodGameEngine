#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>

namespace gge {

class ControlsManager
{
private:
    // Singleton
    static ControlsManager* instance;
    ControlsManager() {};
    
    // Controls
    std::unordered_map<std::string, sf::Keyboard::Key> keyboardControlsMap;
    std::unordered_map<std::string, sf::Mouse::Button> mouseControlsMap;

    // Pressed buffer set {control, was pressed this frame}
    std::unordered_map<sf::Keyboard::Key, bool> pressedKeyboardBuffer;
    std::unordered_map<sf::Mouse::Button, bool> pressedMouseBuffer;

    // Held set
    std::unordered_set<sf::Keyboard::Key> heldKeyboardKeys;
    std::unordered_set<sf::Mouse::Button> heldMouseButtons;
    
public:
    // Methods
    // Set controls
    void setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap);
    void setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap);
    
    // Change control
    void changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey);

    // Is control held now
    bool isHeld(const std::string& controlId);

    // Is control pressed once (set isPressed = false in physics update)
    bool isPressed(const std::string& controlId, bool isPressedNow = true);

    // On control single press
    void controlPress(sf::Keyboard::Key key);
    void controlPress(sf::Mouse::Button button);

    // Clear the vectors of once pressed controls of controls, that were pressed in the past
    void clearPastBuffer();
    // Set all the buffer controls state to past
    void updateBuffer();

    // On control release
    void controlRelease(sf::Keyboard::Key key);
    void controlRelease(sf::Mouse::Button button);

    // Singleton
    static ControlsManager* getInstance();
};

}