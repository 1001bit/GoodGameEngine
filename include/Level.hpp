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

// #define DRAWCOLLIDER

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GDrawable>> gdrawable_ptr_set;
typedef std::unordered_set<std::shared_ptr<Body>> body_ptr_set;
typedef std::unordered_set<std::shared_ptr<GObject>> gobject_ptr_set;

// sizes of the game
constexpr uint GAME_WIDTH = 1440;
constexpr uint GAME_HEIGHT = 880;

class Level : public GObject
{
private:
    // Necessary GObjects
    // game camera that is following some GObject
    std::shared_ptr<Camera> camera;
    // dialogue box
    std::weak_ptr<GSprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<GText> dialogueTextWeak;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;
    // gui view
    sf::View guiView;

    // Updates
    // Update all the GObjects of the level
    void updateLevelObjects(const float& timeMs);
    // Update all the GObjects of the GUI
    void updateGuiObjects(const float& timeMs);

    // Data init patterns
    void initNecessaryGObjects();
    
public:
    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Level GObjects
    // Layers of drawable objects
    std::vector<gdrawable_ptr_set> levelDrawableLayers;
    // Set of body objects
    body_ptr_set levelBodiesSet;
    // Set of other objects
    gobject_ptr_set levelGObjectsSet;
    // set of level GObjects with own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> levelGObjectsWId;

    // GUI GObjects
    // layers of drawable GUI GObjects
    std::vector<gdrawable_ptr_set> guiDrawableLayers;
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
    void update(const float& timeMs);
    // Draw drawable objects
    void drawGObjetcs(sf::RenderWindow& window);
};