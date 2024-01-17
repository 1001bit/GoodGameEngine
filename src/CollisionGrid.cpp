#include "CollisionGrid.hpp"

// Structors
CollisionGrid::CollisionGrid(){
    this->type = TBody;
}

CollisionGrid::~CollisionGrid(){}

// Methods
// init the grid parameters
void CollisionGrid::initGrid(u_char newTileSize, unsigned newHeight, unsigned newWidth){
    tileSize = newTileSize;
    height = newHeight;
    width = newWidth;
    tileGrid = new TileType*[width];
    for (int y = 0; y < height; y++)
    {
        tileGrid[y] = new TileType[height];
    }
};