#include "CollisionGrid.hpp"

// Structors
CollisionGrid::CollisionGrid(){
    this->type = TCollisionGrid;
}

CollisionGrid::~CollisionGrid(){}

// Methods
// init the grid parameters and set the grid from vector
void CollisionGrid::setGrid(std::vector<std::string> stringsVector, u_char newTilePixelSize){
    tilePixelSize = newTilePixelSize;
    mapSize = sf::Vector2u(stringsVector[0].size(), stringsVector.size());
    std::cout << mapSize.x << " " << mapSize.y << "\n";

    // tileMap width
    tileMap = new TileType*[mapSize.y];
    for(uint32_t y = 0; y < mapSize.y; ++y){
        // tileMap height
        tileMap[y] = new TileType[mapSize.x];
        for(uint32_t x = 0; x < mapSize.x; ++x){
            tileMap[y][x] = static_cast<TileType>(static_cast<int>(stringsVector[y][x] - '0'));
        }
    }

    setRectPixelSize(mapSize.x * tilePixelSize, mapSize.y * tilePixelSize);
};

// get overlap of collision of self and other rect
sf::FloatRect CollisionGrid::getOverlapWith(const sf::FloatRect& otherRect){
    const unsigned realTileSize = tilePixelSize * SPRITE_SCALE;
    sf::FloatRect overlap;

    // other rect part that is inside of collision grid
    sf::FloatRect overlapWGrid;
    otherRect.intersects(getRect(), overlapWGrid);
    if(overlapWGrid == sf::FloatRect()){
        return overlap;
    }

    // algorithm
    // rect, which represents the tile area of collision
    sf::Rect<unsigned> tileOverlap;
    tileOverlap.width = overlapWGrid.width/realTileSize;
    tileOverlap.height = overlapWGrid.height/realTileSize;
    tileOverlap.left = overlapWGrid.left/realTileSize;
    tileOverlap.top = overlapWGrid.top/realTileSize;

    std::cout << tileOverlap.width << "/" << tileOverlap.height << "\n";
    for(unsigned tileY = tileOverlap.top; tileY <= tileOverlap.top + tileOverlap.height; ++tileY){
        for(unsigned tileX = tileOverlap.left; tileX <= tileOverlap.left + tileOverlap.width; ++tileX){
            std::cout << tileMap[tileY][tileX] << " ";
            if(tileMap[tileY][tileX] == TTSolid){
                if(!overlap.left){
                    overlap.left = tileX*realTileSize;
                }
                if(!overlap.top){
                    overlap.top = tileY*realTileSize;
                }
                if(overlap.width < tileX - tileOverlap.left){
                    overlap.width = (tileX - tileOverlap.left)*realTileSize;
                }
                if(overlap.width < tileY - tileOverlap.top){
                    overlap.width = (tileY - tileOverlap.top)*realTileSize;
                }
            }
        }
        std::cout << "\n";
    }
    
    return overlap;
}

// Getters
// get collision grid map
TileType** const CollisionGrid::getTileGrid(){
    return tileMap;
};

// get tile size
const u_char& CollisionGrid::getTileSize(){
    return tilePixelSize;
};

// get size of map
const sf::Vector2u CollisionGrid::getMapSize(){
    return mapSize;
};