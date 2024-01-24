#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class ResourceManager
{
private:
    // Singleton
    static ResourceManager* instance;
    ResourceManager(){};

    // Storages
    // textures
    sf::Texture nullTexture;
    std::unordered_map<std::string, sf::Texture> textureMap;
    // fonts
    sf::Font nullFont;
    std::unordered_map<std::string, sf::Font> fontMap;

public: 
    // Get resource
    // Texture
    sf::Texture& getTexture(const std::string& path);
    // Font
    sf::Font& getFont(const std::string& path);

    // Singleton
    static ResourceManager* getInstance();
};
