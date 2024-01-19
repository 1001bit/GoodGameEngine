#pragma once

#include "GObject.hpp"

// Types of tiles on grid
enum TileType {
    TTNone,
    TTSolid,
};

class CollisionGrid : public GObject
{
private:
    // Variables
    u_char tileSize;
    uint32_t height;
    uint32_t width;
    TileType** tileGrid;

public:
    // Structors
    CollisionGrid();
    ~CollisionGrid();

    // Methods
    // init the grid parameters and set the grid from vector
    void setGrid(std::vector<std::string> stringsVector, u_char newTileSize);

    // Getters
    // get collision grid map
    TileType** const getTileGrid();
};
