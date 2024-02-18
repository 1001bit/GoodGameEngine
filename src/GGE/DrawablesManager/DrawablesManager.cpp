#include "GGE/DrawablesManager/DrawablesManager.hpp"

using gge::DrawablesManager;

// Structors
DrawablesManager::DrawablesManager(){}
DrawablesManager::~DrawablesManager(){}

// Methods
// Set max layers count
void DrawablesManager::setLayerCount(u_char newLayerCount){
    layerCount = newLayerCount;

    levelDrawableLayers.clear();
    guiDrawableLayers.clear();
    for(int i = 0; i < layerCount; ++i){
        levelDrawableLayers.push_back(std::vector<std::weak_ptr<obj::Drawable>>());
        guiDrawableLayers.push_back(std::vector<std::weak_ptr<obj::Drawable>>());
    }
}

// Insert new drawable
void DrawablesManager::newDrawable(std::shared_ptr<obj::Drawable> drawable, bool isGui, u_char layer){
    if(layer > layerCount){
        layer = layerCount;
    }

    if(isGui){
        guiDrawableLayers.at(layer).push_back(drawable);
    } else {
        levelDrawableLayers.at(layer).push_back(drawable);
    }
}

// Draw everything
void DrawablesManager::draw(sf::RenderWindow& window, const sf::View& levelView, const sf::View& guiView){
    // Level
    window.setView(levelView);
    for(std::vector<std::weak_ptr<obj::Drawable>>& drawablesWeakLayer : levelDrawableLayers){
        // iterate through a single layer
        for(auto it = drawablesWeakLayer.begin(); it != drawablesWeakLayer.end();){
            auto drawable = it->lock();
            if(!drawable){
                it = drawablesWeakLayer.erase(it);
                continue;
            }

            drawable->drawSelf(window);
            ++it;
        }
    }

    // Gui
    window.setView(guiView);
    // iterate through whole drawables vector
    for(std::vector<std::weak_ptr<obj::Drawable>>& drawablesWeakLayer : guiDrawableLayers){
        // iterate through a single layer
        for(auto it = drawablesWeakLayer.begin(); it != drawablesWeakLayer.end();){
            auto drawable = it->lock();
            if(!drawable){
                it = drawablesWeakLayer.erase(it);
                continue;
            }

            drawable->drawSelf(window);
            ++it;
        }
    }
}