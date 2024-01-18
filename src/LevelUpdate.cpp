#include "Level.hpp"

// #define DRAWCOLLIDER

// Methods
// Update all the objects of the game
void Level::updateLevelObjects(sf::RenderWindow& window, const float& timeMs){
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
            body->collide(body2);
        }

        // draw collider for debug
        #ifdef DRAWCOLLIDER
        sf::RectangleShape visible = sf::RectangleShape();
        visible.setFillColor(sf::Color::Red);
        visible.setSize(sf::Vector2f(body->getRect().width, body->getRect().height));
        visible.setPosition(sf::Vector2f(body->getRect().left, body->getRect().top));
        window.draw(visible);
        #endif
    }

    // update other gobjects
    for(std::shared_ptr<GObject> object : levelGObjectsSet){
        object->update(timeMs);
    }

    // draw and update drawables
    for(std::pair<const u_char, gdrawable_ptr_set> drawablesLayer : levelDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer.second){
            // update an object
            drawable->update(timeMs);

            #ifndef DRAWCOLLIDER
            drawable->drawSelf(window);
            #endif
        }
    }
};

// Update all the objects of the GUI
void Level::updateGuiObjects(sf::RenderWindow& window, const float& timeMs){
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
    // draw drawables
    for(std::pair<const u_char, gdrawable_ptr_set> drawablesLayer : guiDrawableLayers){
        // iterate through a single layer
        for(std::shared_ptr<GDrawable> drawable : drawablesLayer.second){
            drawable->update(timeMs);
            drawable->drawSelf(window);
        }
    }
};

// Update states of all the objects
void Level::update(sf::RenderWindow& window, const float& timeMs){
    window.setView(camera->getView());
    updateLevelObjects(window, timeMs);
    window.setView(guiView);
    updateGuiObjects(window, timeMs);
};