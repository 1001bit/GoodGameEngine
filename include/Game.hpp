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
#include "Level.hpp"

// // Set of GObjects
// typedef std::unordered_set<std::shared_ptr<GObject>> GObjectSet;

// // Types of layers
// enum GameLayerType {
//     LBodies,
//     LInvisibles,
//     LCamera,
//     Drawables
// };

// // sizes of the game
// constexpr uint GAME_WIDTH = 1440;
// constexpr uint GAME_HEIGHT = 880;

class Game : public GObject
{
private:
    // Variables
    // pointer to the level
    std::shared_ptr<Level> currentLevel;

    // Methods
    // Handle window events
    void handleEvent(const sf::Event& event);

    // Inits
    void initControls();

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