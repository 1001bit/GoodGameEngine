#include "Level.hpp"

// Structors
Level::Level(){}

Level::~Level(){
    std::cout << "2\n";
}

// Methods
// Create new object for game
void Level::addNewLevelObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer, uint16_t id){
    if(newParent == nullptr){
        newParent = shared_from_this();
    }

    // first three layers are for non-drawable GObjects
    if(DRAWABLE_GOBJECT_TYPES.count(newGObject->getType())){
        layer += GameLayerType::Drawables;
    } 
    // very first layer is for bodies
    else if (BODY_GOBJECT_TYPES.count(newGObject->getType())) {
        layer = GameLayerType::LBodies;
    }
    // second layer is for all other types
    else {
        layer = GameLayerType::LInvisibles;
    }

    // add to object with id if it's not 0
    if(id != 0){
        LevelObjectsWId[id] = newGObject;
    }

    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GameLayers.count(layer)){
        GameLayers[layer] = GObjectPtrSet{};
    }
    GameLayers[layer].insert(newGObject);
};

// Create new object for gui
void Level::addNewGuiObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer){
    if(newParent == nullptr){
        newParent = shared_from_this();
    }

    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GuiLayers.count(layer)){
        GuiLayers[layer] = GObjectPtrSet{};
    }
    GuiLayers[layer].insert(newGObject);
};