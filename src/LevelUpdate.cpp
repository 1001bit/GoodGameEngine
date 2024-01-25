#include "Level.hpp"

// Methods
// Update all the objects of the GUI
void Level::updateCurrentDialogue(){
    // if current dialogue is active
    if(auto currentDialogue = currentDialogueWeak.lock()){
        currentDialogue->update();
        // set camera target
        if(auto currentSpeaker = levelGObjectsWId.at(currentDialogue->getCurrentLine().characterId).lock()){
            camera->setTarget(currentSpeaker);
        }
        // set dialogue text
        if(auto dialogueText = dialogueTextWeak.lock()){
            dialogueText->text.setString(currentDialogue->getCurrentLine().line);
        }

        // if empty string (after last line) - stop it
        if(currentDialogue->getCurrentLine().line == ""){
            currentDialogueWeak.reset();
            if(auto dialogueBox = dialogueBoxWeak.lock()){
                dialogueBox->setRelativePos(9999, 9999);
            }
        }
    }
};

void Level::update(const float& timeMs){
    GObject::update(timeMs);
    
    camera->update(timeMs);
    updateCurrentDialogue();
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