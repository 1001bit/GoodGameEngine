#pragma once

#include <map>
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

class Game : public GObject
{
private:
    // Variables
    // pointer to the game itself
    std::shared_ptr<GObject> gamePtr;

    // layers of game objects
    std::map<u_char, GObjectSet> GameLayers;
    // layers of GUI objects
    std::map<u_char, GObjectSet> GuiLayers;

    // set of objects with own id
    std::unordered_map<uint16_t, std::shared_ptr<GObject>> GameObjectsWId;

    // set of dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;

    // gui view
    sf::View guiView;

    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;
    // storage of the fonts
    std::unordered_map<std::string, sf::Font> fontMap;


    // Needed Object
    // game camera
    std::shared_ptr<Camera> camera;
    // dialogue box
    std::shared_ptr<GSprite> dialogueBox;
    // dialogue text
    std::shared_ptr<GText> dialogueText;
    // current dialogue
    std::shared_ptr<Dialogue> currentDialogue;

    // Methods
    // Update states of all the objects
    void update(sf::RenderWindow& window, const float& timeMs);
    // Handle window events
    void handleEvent(const sf::Event& event);
    // Update all the objects of the game
    void updateGameObjects(sf::RenderWindow& window, const float& timeMs);
    // Update all the objects of the GUI
    void updateGuiObjects(sf::RenderWindow& window, const float& timeMs);
    // Create new object for game
    void addNewGameObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, u_char layer = 0, uint16_t id = 0);
    // Create new object for gui
    void addNewGuiObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, u_char layer);
    // Init all the objects, that are needed for gameplay
    void initGObjects();

public:
    // Structors
    Game();
    ~Game();

    // Methods
    // Init game
    void init();

    // Main game loop
    void loop(sf::RenderWindow& window);
};