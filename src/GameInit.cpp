#include "Game.hpp"

// Methods

// init all the objects
void Game::initGObjects(){
    // Game
    // init camera
    camera = std::make_shared<Camera>();
    addNewGameObject(camera, gamePtr);
    camera->setSize(GAME_WIDTH, GAME_HEIGHT);

    // init dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    addNewGameObject(dummy, gamePtr, 0, 1);
    dummy->setRectSize(16, 16);
    dummy->setRelativePos(500, 300);
    camera->setTarget(dummy);
    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    addNewGameObject(dummySprite, dummy, 1);
    dummySprite->insertAnimation("idle", Animation(textureMap.at("Original/dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // and his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    addNewGameObject(sword, dummy, 2);
    sword->setTexture(textureMap.at("Original/sword.png"));
    sword->setRelativePos(-30, 1);

    // Npc
    std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    addNewGameObject(npc, gamePtr, 0, 2);
    npc->setRectSize(16, 16);
    npc->setRelativePos(500, 300);
    // his sprite
    std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    addNewGameObject(npcSprite, npc, 1);
    npcSprite->insertAnimation("idle", Animation(textureMap.at("Original/dummy.png"), 16, 500, 1));
    npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<SolidBody> platform = std::make_shared<SolidBody>();
    addNewGameObject(platform, gamePtr);
    platform->setRectSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    addNewGameObject(platformSprite, platform, 0);
    platformSprite->setTexture(textureMap.at("Original/platform.png"));

    // 2nd platform
    std::shared_ptr<SolidBody> platform2 = std::make_shared<SolidBody>();
    addNewGameObject(platform2, gamePtr);
    platform2->setRectSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    addNewGameObject(platformSprite2, platform2, 0);
    platformSprite2->setTexture(textureMap.at("Original/platform.png"));

    // 3rd platform
    std::shared_ptr<SolidBody> platform3 = std::make_shared<SolidBody>();
    addNewGameObject(platform3, gamePtr);
    platform3->setRectSize(100, 10);
    platform3->setRelativePos(-600, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite3 = std::make_shared<GSprite>();
    addNewGameObject(platformSprite3, platform3, 0);
    platformSprite3->setTexture(textureMap.at("Original/platform.png"));

    /////////////////////
    // Gui
    // Dialogue box
    dialogueBox = std::make_shared<GSprite>();
    addNewGuiObject(dialogueBox, gamePtr, 0);
    dialogueBox->setTexture(textureMap.at("Original/dialogueBackground.png"));
    dialogueBox->setRelativePos((GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600); // centralize it on X position
    
    // Dialogue text
    dialogueText = std::make_shared<GText>();
    addNewGuiObject(dialogueText, dialogueBox, 1);
    dialogueText->text.setFont(fontMap["Original/font1.ttf"]);
    dialogueText->text.setCharacterSize(30);
    dialogueText->text.setString("Hi");
    dialogueText->setRelativePos(60, 20);

    // dummy-npc dialogue
    std::shared_ptr<Dialogue> dialogue1 = std::make_shared<Dialogue>();
    dialogues.insert({0, dialogue1});
    dialogue1->setLines({
        {1, "hello"},
        {2, "hi"},
        {1, "bye"},
        {2, "goodbye"}
    });
    currentDialogue = dialogue1;
}

// add new object to the game
void Game::addNewGameObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer, uint16_t id){
    // first three layers are for non-drawable GObjects
    if(DRAWABLE_GOBJECT_TYPES.count(newGObject->getType())){
        layer += GameLayerType::Drawables;
    } 
    // very first layer is for bodies
    else if (BODY_GOBJECT_TYPES.count(newGObject->getType())) {
        layer = GameLayerType::LBodies;
    } 
    // third layer is for camera only
    else if (newGObject->getType() == TCamera){
        layer = GameLayerType::LCamera;
    } 
    // second layer is for all other types
    else {
        layer = GameLayerType::LInvisibles;
    }

    // add to object with id if it's not 0
    if(id != 0){
        GameObjectsWId[id] = newGObject;
    }

    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GameLayers.count(layer)){
        GameLayers[layer] = GObjectSet{};
    }
    GameLayers[layer].insert(newGObject);
}

// add new object to the gui
void Game::addNewGuiObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer){
    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GuiLayers.count(layer)){
        GuiLayers[layer] = GObjectSet{};
    }
    GuiLayers[layer].insert(newGObject);
}