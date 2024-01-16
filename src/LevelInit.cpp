#include "Level.hpp"

// GObjects
// necessary
void Level::initNecessaryGObjects(){
    // Level
    // init camera
    camera = std::make_shared<Camera>();
    addNewLevelObject(camera, levelPtr);
    camera->setSize(GAME_WIDTH, GAME_HEIGHT);

    /////////////////////
    // Gui
    // Dialogue box
    dialogueBox = std::make_shared<GSprite>();
    addNewGuiObject(dialogueBox, levelPtr, 0);
    dialogueBox->setTexture(textureMap.at("dialogueBackground.png"));
    dialogueBox->setRelativePos((GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600); // centralize it on X position
    
    // Dialogue text
    dialogueText = std::make_shared<GText>();
    addNewGuiObject(dialogueText, dialogueBox, 1);
    dialogueText->text.setFont(fontMap["font1.ttf"]);
    dialogueText->text.setCharacterSize(30);
    dialogueText->text.setString("Hi");
    dialogueText->setRelativePos(60, 20);
};

// test
void Level::initTestGObjects(){
    // Level
    // init dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    addNewLevelObject(dummy, levelPtr, 0, 1);
    dummy->setRectSize(16, 16);
    dummy->setRelativePos(500, 300);
    camera->setTarget(dummy);
    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    addNewLevelObject(dummySprite, dummy, 1);
    dummySprite->insertAnimation("idle", Animation(textureMap.at("dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // and his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    addNewLevelObject(sword, dummy, 2);
    sword->setTexture(textureMap.at("sword.png"));
    sword->setRelativePos(-30, 1);

    // Npc
    std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    addNewLevelObject(npc, levelPtr, 0, 2);
    npc->setRectSize(16, 16);
    npc->setRelativePos(500, 300);
    // his sprite
    std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    addNewLevelObject(npcSprite, npc, 1);
    npcSprite->insertAnimation("idle", Animation(textureMap.at("dummy.png"), 16, 500, 1));
    npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<SolidBody> platform = std::make_shared<SolidBody>();
    addNewLevelObject(platform, levelPtr);
    platform->setRectSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    addNewLevelObject(platformSprite, platform, 0);
    platformSprite->setTexture(textureMap.at("platform.png"));

    // 2nd platform
    std::shared_ptr<SolidBody> platform2 = std::make_shared<SolidBody>();
    addNewLevelObject(platform2, levelPtr);
    platform2->setRectSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    addNewLevelObject(platformSprite2, platform2, 0);
    platformSprite2->setTexture(textureMap.at("platform.png"));

    // 3rd platform
    std::shared_ptr<SolidBody> platform3 = std::make_shared<SolidBody>();
    addNewLevelObject(platform3, levelPtr);
    platform3->setRectSize(100, 10);
    platform3->setRelativePos(-600, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite3 = std::make_shared<GSprite>();
    addNewLevelObject(platformSprite3, platform3, 0);
    platformSprite3->setTexture(textureMap.at("platform.png"));

    /////////////////////
    // Gui
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
};

// Assets
// necessary
void Level::initNecessaryAssets(){
    // texture
    sf::Texture texture;
    texture.loadFromFile("Assets/Textures/dialogueBackground.png");
    textureMap["dialogueBackground.png"] = texture;

    // font
    sf::Font font;
    font.loadFromFile("Assets/Fonts/font1.ttf");
    fontMap["font1.ttf"] = font;
};

// test
void Level::initTestAssets(){
    // texture
    sf::Texture texture;
    texture.loadFromFile("Assets/Textures/dummy.png");
    textureMap["dummy.png"] = texture;
    texture.loadFromFile("Assets/Textures/sword.png");
    textureMap["sword.png"] = texture;
    texture.loadFromFile("Assets/Textures/platform.png");
    textureMap["platform.png"] = texture;
};


// All
// Init level
void Level::init(){
    levelPtr = shared_from_this();

    // init gui view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);

    // init object
    initNecessaryAssets();
    initNecessaryGObjects();
    initTestAssets();
    initTestGObjects();
};