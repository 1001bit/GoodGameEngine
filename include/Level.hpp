#pragma once

#include "GObject.hpp"
#include "AnimatedSprite.hpp"
#include "GSprite.hpp"
#include "PhysPlayer.hpp"
#include "Camera.hpp"
#include "SolidBody.hpp"
#include "TDPlayer.hpp"
#include "TDNpc.hpp"
#include "PhysNpc.hpp"
#include "GText.hpp"
#include "Dialogue.hpp"

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GObject>> GObjectSet;

// Types of layers
enum GameLayerType {
    LBodies,
    LInvisibles,
    LCamera,
    Drawables
};

// sizes of the game
constexpr uint GAME_WIDTH = 1440;
constexpr uint GAME_HEIGHT = 880;

class Level : public GObject
{
private:
    // GObjects
    // Self level pointer
    std::shared_ptr<GObject> levelPtr;

    // layers of level GObjects
    std::map<u_char, GObjectSet> GameLayers;
    // layers of GUI GObjects
    std::map<u_char, GObjectSet> GuiLayers;

    // set of GObjects with own id
    std::unordered_map<uint16_t, std::shared_ptr<GObject>> LevelObjectsWId;

    // set of dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;

    // Storages
    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;
    // storage of the fonts
    std::unordered_map<std::string, sf::Font> fontMap;

    // Necessary GObjects
    // game camera that is following some GObject
    std::shared_ptr<Camera> camera;
    // dialogue box
    std::shared_ptr<GSprite> dialogueBox;
    // dialogue text inside a box
    std::shared_ptr<GText> dialogueText;
    // current dialogue
    std::shared_ptr<Dialogue> currentDialogue;
    // gui view
    sf::View guiView;

    // Create GObjects patterns
    // Create new object for game
    void addNewLevelObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer = 0, uint16_t id = 0);
    // Create new object for gui
    void addNewGuiObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer);

    // Updates
    // Update all the GObjects of the level
    void updateLevelObjects(sf::RenderWindow& window, const float& timeMs);
    // Update all the GObjects of the GUI
    void updateGuiObjects(sf::RenderWindow& window, const float& timeMs);

    // GObjects init patterns
    // GObjects inits 
    void initDummyGObjects();
    // Assets inits
    void initDummyAssets();
    
public:
    // Structors
    Level();
    ~Level();

    // Methods
    // Init level
    void init();
    // Update states of all the objects
    void update(sf::RenderWindow& window, const float& timeMs);
    // Load level from file
    void loadFromFile(const sf::String& fileName);
};