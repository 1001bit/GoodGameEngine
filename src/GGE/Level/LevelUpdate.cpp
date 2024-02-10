#include "GGE/Level.hpp"

using gge::Level;

// Methods
// Update everything in the level
void Level::update(const float& dTimeMs){
    for(auto it = updatableGObjects.begin(); it != updatableGObjects.end();){
        auto object = it->lock();
        if(!object){
            it = updatableGObjects.erase(it);
            continue;
        }

        object->update(dTimeMs);

        ++it;
    }
};

// Update dialogues
void Level::updateDialogues(){
    dialogueManager.updateCurrentDialogue(levelGObjectsWId, camera);
}

// draw drawables
void Level::drawGObjetcs(sf::RenderWindow& window){
    // Level
    window.setView(camera->getView());
    // iterate through whole drawables vector
    for(std::vector<std::weak_ptr<GDrawable>>& drawablesWeakLayer : levelDrawableLayers){
        // iterate through a single layer
        for(auto it = drawablesWeakLayer.begin(); it != drawablesWeakLayer.end();){
            auto drawable = it->lock();
            if(!drawable){
                it = drawablesWeakLayer.erase(it);
                continue;
            }

            // draw object if it's in bounds of the camera
            if(camera->getRect().intersects(drawable->getRect())){
                drawable->drawSelf(window);
            }
            ++it;
        }
    }

    // Gui
    window.setView(guiView);
    // iterate through whole drawables vector
    for(std::vector<std::weak_ptr<GDrawable>>& drawablesWeakLayer : guiDrawableLayers){
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