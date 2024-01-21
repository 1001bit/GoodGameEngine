#pragma once

#include "Level.hpp"

class Game
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
    void initCooldowns();

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