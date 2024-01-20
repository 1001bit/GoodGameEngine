#pragma once

#include "Body.hpp"
#include <cmath>

// Types of tiles on map
enum TileType {
    TTNone,
    TTSolid,
};

class CollisionGrid : public Body
{
private:
    // Variables
    u_char tilePixelSize;
    sf::Vector2u mapSize;
    TileType** tileMap;

public:
    // Structors
    CollisionGrid();
    ~CollisionGrid();

    // Methods
    // init the grid parameters and set the grid from vector
    void setGrid(std::vector<std::string> stringsVector, u_char newTilePixelSize);
    // get overlap of collision of self and other rect
    virtual sf::FloatRect getOverlapWith(const sf::FloatRect& otherRect);

    // Getters
    // get collision grid map
    TileType** const getTileGrid();
    // get tile size
    const u_char& getTileSize();
    // get size of map
    const sf::Vector2u getMapSize();
};
