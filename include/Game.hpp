#pragma once

#include "Level.hpp"

// Framerate limits
constexpr unsigned MAX_FPS = 120;
constexpr unsigned MIN_FPS = 90;

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