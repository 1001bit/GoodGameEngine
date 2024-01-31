#include "GGE/SingletonManagers/ResourceManager.hpp"

// Singleton
ResourceManager* ResourceManager::instance = nullptr;
ResourceManager* ResourceManager::getInstance(){
    if (!instance)
        instance = new ResourceManager();
    return instance;
}

// Get resource
// Texture
sf::Texture& ResourceManager::getTexture(const std::string& path){
    if(!textureCache.count(path)){
        sf::Texture newTexture;

        if(!newTexture.loadFromFile(path)){
            std::cout << "couldn't load file at " << path << "\n"; 
            return nullTexture;
        }

        textureCache[path] = newTexture;
    }

    return textureCache.at(path);
};

// Font
sf::Font& ResourceManager::getFont(const std::string& path){
    if(!fontCache.count(path)){
        sf::Font newFont;

        if(!newFont.loadFromFile(path)){
            std::cout << "couldn't load file at " << path << "\n"; 
            return nullFont;
        }

        fontCache[path] = newFont;
    }
    
    return fontCache.at(path);
};