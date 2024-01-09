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

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GObject>> GObjectSet;

// Types of layers
enum LayerType {
    LBodies = 0,
    LInvisibles = 1,
    LCamera = 2
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

    // game camera
    std::shared_ptr<Camera> camera;
    // gui view
    sf::View guiView;

    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;
    // storage of the fonts
    std::unordered_map<std::string, sf::Font> fontMap;

    // Methods
    // Update states of all the objects
    void update(sf::RenderWindow& window, const float& timeMs);
    // Update all the objects of the game
    void updateGame(sf::RenderWindow& window, const float& timeMs);
    // Update all the objects of the GUI
    void updateGui(sf::RenderWindow& window, const float& timeMs);
    // Create new object for game
    void addNewGameObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, u_char layer);
    // Create new object for gui
    void addNewGuiObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, u_char layer);
    // Init new object
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