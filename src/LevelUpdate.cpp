#include "Level.hpp"

// Methods
// Update all the objects of the game
void Level::updateLevelObjects(const float& timeMs){
    // update and collide bodies
    for(std::shared_ptr<Body> body : levelBodiesSet){
        body->update(timeMs);

        // don't collide if no collider
        if(body->getRect() == sf::FloatRect()){
            continue;
        }

        // collide body with other body 
        for(std::shared_ptr<Body> body2 : levelBodiesSet){
            if(body2 == body || body2->getRect() == sf::FloatRect()){
                continue;
            }
            body->collideWith(body2);
        }
    }

    // update other gobjects
    for(std::shared_ptr<GObject> object : levelGObjectsSet){
        object->update(timeMs);
    }

    // draw and update drawables
    for(gdrawable_ptr_set drawablesLayer : levelDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer){
            // update an object
            drawable->update(timeMs);
        }
    }
};

// Update all the objects of the GUI
void Level::updateGuiObjects(const float& timeMs){
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

    // iterate through whole map
    for(gdrawable_ptr_set drawablesLayer : guiDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer){
            drawable->update(timeMs);
        }
    }
};

// draw drawables
void Level::drawGObjetcs(sf::RenderWindow& window){
    // Level
    window.setView(camera->getView());
    // iterate through whole map
    for(gdrawable_ptr_set drawablesLayer : levelDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer){
            // update an object
            drawable->drawSelf(window);
        }
    }

    // Gui
    window.setView(guiView);
    for(gdrawable_ptr_set drawablesLayer : guiDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer){
            drawable->drawSelf(window);
        }
    }
}

// Update states of all the objects
void Level::update(const float& timeMs){
    updateLevelObjects(timeMs);
    updateGuiObjects(timeMs);
};