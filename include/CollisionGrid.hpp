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
    unsigned height;
    unsigned width;
    TileType** tileGrid;

public:
    // Structors
    CollisionGrid();
    ~CollisionGrid();

    // Methods
    // init the grid parameters
    void initGrid(u_char newTileSize, unsigned newHeight, unsigned newWidth);
};
