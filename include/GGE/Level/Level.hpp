#pragma once

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/AnimatedSprite.hpp"
#include "GGE/GObjects/GSprite.hpp"
#include "GGE/GObjects/PhysPlayer.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/GObjects/Body.hpp"
#include "GGE/GObjects/TDPlayer.hpp"
#include "GGE/GObjects/TDNpc.hpp"
#include "GGE/GObjects/PhysNpc.hpp"
#include "GGE/GObjects/GText.hpp"
#include "GGE/GObjects/GDrawable.hpp"

#include "GGE/Level/Dialogue.hpp"

#include "GGE/SingletonManagers/ResourceManager.hpp"
#include "GGE/SingletonManagers/PhysicsManager.hpp"

// #define DRAWCOLLIDER

// sizes of the game
constexpr uint GAME_WIDTH = 1440;
constexpr uint GAME_HEIGHT = 880;

class Level : public GObject
{
private:
    // Necessary GObjects
    // dialogue box
    std::weak_ptr<GSprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<GText> dialogueTextWeak;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;
    // gui view
    sf::View guiView;

    // Updates
    // Update all the GObjects of the GUI
    void updateCurrentDialogue();

    // Data init patterns
    void initNecessaryGObjects();
    
public:
    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Drawable Level GObjects
    std::vector< std::vector<std::weak_ptr<GDrawable>> > levelDrawableLayers;
    // Level GObjects with own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> levelGObjectsWId;
    // Game camera that is following some GObject
    std::shared_ptr<Camera> camera;

    // GUI GObjects
    // layers of drawable GUI GObjects
    std::vector< std::vector<std::weak_ptr<GDrawable>> > guiDrawableLayers;
    // set of dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;
    ///////////////////////////

    // Methods
    // Init level
    void init();
    // Load level from file
    void loadFromFile(const sf::String& fileName);
    // test inits
    void initTestGObjects();

    // Update states of all the objects
    void update(const float& dTimeMs);
    // Draw drawable objects
    void drawGObjetcs(sf::RenderWindow& window);
};