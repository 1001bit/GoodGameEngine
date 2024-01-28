#pragma once

#include "GObject.hpp"
#include "AnimatedSprite.hpp"
#include "GSprite.hpp"
#include "PhysPlayer.hpp"
#include "Camera.hpp"
#include "Body.hpp"
#include "TDPlayer.hpp"
#include "TDNpc.hpp"
#include "PhysNpc.hpp"
#include "GText.hpp"
#include "Dialogue.hpp"
#include "GDrawable.hpp"
#include "ResourceManager.hpp"
#include "PhysicsManager.hpp"

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