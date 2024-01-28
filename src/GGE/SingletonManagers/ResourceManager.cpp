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
    if(textureMap.count(path)){
        return textureMap.at(path);
    }

    sf::Texture newTexture;

    if(!newTexture.loadFromFile(path)){
        std::cout << "couldn't load file at " << path << "\n"; 
        return nullTexture;
    }

    textureMap[path] = newTexture;
    return textureMap.at(path);
};

// Font
sf::Font& ResourceManager::getFont(const std::string& path){
    if(fontMap.count(path)){
        return fontMap.at(path);
    }

    sf::Font newFont;

    if(!newFont.loadFromFile(path)){
        std::cout << "couldn't load file at " << path << "\n"; 
        return nullFont;
    }

    fontMap[path] = newFont;
    return fontMap.at(path);
};