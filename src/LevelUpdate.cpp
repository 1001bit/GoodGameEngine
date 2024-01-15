#include "Level.hpp"

// Methods
// Update all the objects of the game
void Level::updateLevelObjects(sf::RenderWindow& window, const float& timeMs){
    // iterate through whole map
    for(std::pair<const u_char, GObjectSet> GObjectsLayer : GameLayers){
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
};

// Update all the objects of the GUI
void Level::updateGuiObjects(sf::RenderWindow& window, const float& timeMs){
    if(currentDialogue != nullptr){
        currentDialogue->update();
    }

    // iterate through whole map
    for(std::pair<const u_char, GObjectSet> GObjectsLayer : GuiLayers){
        for(std::shared_ptr<GObject> object : GObjectsLayer.second){
            if(!DRAWABLE_GOBJECT_TYPES.count(object->getType())){
                continue;
            }

            // update dialogue
            if(object == dialogueBox || object == dialogueText){
                // if current dialogue is not active - skip
                if(currentDialogue == nullptr){
                    continue;
                }
                // if current active dialogue had ended - skip
                if(currentDialogue->getCurrentLine().line == ""){
                    currentDialogue = nullptr;
                    camera->setTarget(LevelObjectsWId.at(1));
                    continue;
                }

                // set text of current line
                dialogueText->text.setString(currentDialogue->getCurrentLine().line);
                // point camera to talker
                camera->setTarget(LevelObjectsWId.at(currentDialogue->getCurrentLine().characterId));
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