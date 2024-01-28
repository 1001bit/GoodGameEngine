#pragma once

#include "GGE/Level/Level.hpp"
#include "GGE/GameConstants.hpp"

class Game
{
private:
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

    // Variables
    // pointer to the level
    std::shared_ptr<Level> currentLevel;
};