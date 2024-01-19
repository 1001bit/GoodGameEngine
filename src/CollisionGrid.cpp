#include "CollisionGrid.hpp"

// Structors
CollisionGrid::CollisionGrid(){
    this->type = TCollisionGrid;
}

CollisionGrid::~CollisionGrid(){}

// Methods
// init the grid parameters and set the grid from vector
void CollisionGrid::setGrid(std::vector<std::string> stringsVector, u_char newTileSize){
    tileSize = newTileSize;
    height = stringsVector.size();
    width = stringsVector[0].size();

    for(uint32_t y = 0; y < height; ++y){
        for(uint32_t x = 0; x < width; ++x){
            if(stringsVector[y].size() < x){
                break;
            }
            tileGrid[y][x] = static_cast<TileType>(stringsVector[y][x]);
        }
    }
};

// Getters
// get collision grid map
TileType** const CollisionGrid::getTileGrid(){
    return tileGrid;
};