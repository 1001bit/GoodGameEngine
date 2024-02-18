#pragma once

#include "GGE/GObjects/Drawable.hpp"

namespace gge{

class DrawablesManager
{
private:
    // Levels of drawable gobjects
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > levelDrawableLayers;
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > guiDrawableLayers;

    u_char layerCount;

public:
    // Structors
    DrawablesManager();
    ~DrawablesManager();

    // Methods
    // Insert new drawable
    void newDrawable(std::shared_ptr<obj::Drawable> drawable, bool isGui, u_char layer);
    // Draw everything
    void draw(sf::RenderWindow& window, const sf::View& levelView, const sf::View& guiView);
    // Set max layers count
    void setLayerCount(u_char newLayerCount);
};

}