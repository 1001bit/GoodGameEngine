#include "GGE/Level.hpp"

// Methods
// Update everything in the level
void Level::update(const float& dTimeMs){
    dialogueManager.updateCurrentDialogue();

    // set camera target from dialogue
    uint16_t speakerId = dialogueManager.getCurrentSpeakerId();
    std::shared_ptr<GObject> currentSpeaker = levelGObjectsWId.at(1).lock();
    if(levelGObjectsWId.count(speakerId)){
        currentSpeaker = levelGObjectsWId.at(speakerId).lock();
        if(!currentSpeaker){
            levelGObjectsWId.erase(speakerId);
            currentSpeaker = levelGObjectsWId.at(1).lock();
        }
    }
    camera->setTarget(currentSpeaker);

    GObject::update(dTimeMs);
};

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