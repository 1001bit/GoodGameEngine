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
typedef std::unordered_set<std::shared_ptr<GObject>> GObjectPtrSet;

// Types of layers
enum GameLayerType {
    LBodies,
    LInvisibles,
    Drawables
};

// sizes of the game
constexpr uint GAME_WIDTH = 1440;
constexpr uint GAME_HEIGHT = 880;

class Level : public GObject
{
private:
    // GObjects

    // layers of level GObjects
    std::map<u_char, GObjectPtrSet> GameLayers;
    // layers of GUI GObjects
    std::map<u_char, GObjectPtrSet> GuiLayers;
    // set of dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;

    // set of GObjects with own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> LevelObjectsWId;

    // Storages
    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;
    // storage of the fonts
    std::unordered_map<std::string, sf::Font> fontMap;

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

    // Data init patterns
    void initNecessaryGObjects();
    void initNecessaryAssets();
    
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

    // test inits
    void initTestGObjects();
    void initTestAssets();
};