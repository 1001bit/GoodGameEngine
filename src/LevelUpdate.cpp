#include "Level.hpp"

// Methods
// Update all the objects of the GUI
void Level::updateCurrentDialogue(){
    // if current dialogue is active
    auto currentDialogue = currentDialogueWeak.lock();
    if(!currentDialogue){
        return;
    }

    currentDialogue->update();

    // if no current speaker - stop dialogue
    if(!levelGObjectsWId.count(currentDialogue->getCurrentLine().characterId)){
        currentDialogueWeak.reset();
        if(auto dialogueBox = dialogueBoxWeak.lock()){
            dialogueBox->setRelativePos(9999, 9999);
        }
        return;
    };

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
    std::cout << "\n";
};

void Level::update(const float& timeMs){
    updateCurrentDialogue();

    GObject::update(timeMs);
    
    camera->update(timeMs);
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