#include "Level.hpp"

// Methods
// Update all the objects of the game
void Level::updateLevelObjects(sf::RenderWindow& window, const float& timeMs){
    // iterate through whole map
    for(std::pair<const u_char, gobject_ptr_set> GObjectsLayer : GameLayers){
        // iterate through a single layer
        for(std::shared_ptr<GObject> object : GObjectsLayer.second){
            // update an object
            object->update(timeMs);

            // if current layer == body layer: collide
            if(GObjectsLayer.first == GameLayerType::LBodies && object->getRect() != sf::FloatRect() && object->getType() == TKinematicBody){
                // collide body with other bodies
                for(std::shared_ptr<GObject> Object2 : GObjectsLayer.second){
                    if(Object2 == object || Object2->getRect() == sf::FloatRect()){
                        continue;
                    }
                    object->collide(Object2);
                }

                // draw collider for debug
                #ifdef DRAWCOLLIDER
                sf::RectangleShape visible = sf::RectangleShape();
                visible.setFillColor(sf::Color::Red);
                visible.setSize(sf::Vector2f(object->getCollider().width, object->getCollider().height));
                visible.setPosition(sf::Vector2f(object->getCollider().left, object->getCollider().top));
                window.draw(visible);
                #endif
            }

            #ifndef DRAWCOLLIDER
            // if drawable - draw on a screen
            if(DRAWABLE_GOBJECT_TYPES.count(object->getType())){
                object->drawSelf(window);
            }
            #endif
        }
    }
    camera->update(timeMs);
};

// Update all the objects of the GUI
void Level::updateGuiObjects(sf::RenderWindow& window, const float& timeMs){
    // if current dialogue is active
    if(auto currentDialogue = currentDialogueWeak.lock()){
        currentDialogue->update();
        // set camera target
        if(auto currentSpeaker = LevelObjectsWId.at(currentDialogue->getCurrentLine().characterId).lock()){
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
    for(std::pair<const u_char, gobject_ptr_set> GObjectsLayer : GuiLayers){
        for(std::shared_ptr<GObject> object : GObjectsLayer.second){
            if(!DRAWABLE_GOBJECT_TYPES.count(object->getType())){
                continue;
            }
            object->drawSelf(window);
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