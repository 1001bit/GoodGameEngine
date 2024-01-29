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
    }
    camera->setTarget(currentSpeaker);

    GObject::update(dTimeMs);
};

// draw drawables
void Level::drawGObjetcs(sf::RenderWindow& window){
    // Level
    window.setView(camera->getView());
    for(std::vector<std::weak_ptr<GDrawable>> drawablesWeakLayer : levelDrawableLayers){
        // iterate through a single layer
        for(std::weak_ptr<GDrawable> drawableWeak : drawablesWeakLayer){
            // draw an object
            if(auto drawable = drawableWeak.lock()){
                drawable->drawSelf(window);
            }
        }
    }

    // Gui
    window.setView(guiView);
    for(std::vector<std::weak_ptr<GDrawable>> drawablesWeakLayer : guiDrawableLayers){
        // iterate through a single layer
        for(std::weak_ptr<GDrawable> drawableWeak : drawablesWeakLayer){
            // draw an object
            if(auto drawable = drawableWeak.lock()){
                drawable->drawSelf(window);
            }
        }
    }
}