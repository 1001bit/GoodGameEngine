#pragma once

#include <iostream>
#include <map>
#include "GObject.hpp"
#include "AnimatedSprite.hpp"
#include "GSprite.hpp"

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GObject>> GObjectSet;

class Game : public GObject
{
private:
    // Variables
    // layers of objects
    std::map<u_char, GObjectSet> GObjectsLayers;
    // pointer to the game itself
    std::shared_ptr<GObject> gamePtr;

    // Methods
    // Main game loop
    void loop(sf::RenderWindow& window);
    // Update states of all the objects and draw them
    void update(sf::RenderWindow& window, const float& timeMs);
    // Create new object
    void createNewGObject(std::shared_ptr<GObject>, std::shared_ptr<GObject> newParent, int layer);

public:
    // Structors
    Game();
    ~Game();

    // Methods
    // Init game
    void init(sf::VideoMode mode, const sf::String& title, sf::Uint32 style);
};