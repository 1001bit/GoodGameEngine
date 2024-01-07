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

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GObject>> GObjectSet;

// Types of layers
enum LayerType {
    LBodies = 0,
    LInvisibles = 1,
    LCamera = 2
};

class Game : public GObject
{
private:
    // Variables
    // layers of objects
    std::map<u_char, GObjectSet> GObjectsLayers;
    // pointer to the game itself
    std::shared_ptr<GObject> gamePtr;
    // main camera
    std::shared_ptr<Camera> camera;
    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;

    // Methods
    // Update states of all the objects and draw them
    void update(sf::RenderWindow& window, const float& timeMs);
    // Create new object
    void createNewGObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, u_char layer);

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