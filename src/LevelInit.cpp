#include "Level.hpp"

// Test
// GObjects
void Level::initTestGObjects(){
    // Level
    // dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    dummy->setParent(shared_from_this());
    levelBodiesSet.insert(dummy);
    levelGObjectsWId[1] = dummy;
    dummy->setRectPixelSize(16, 16);
    dummy->setRelativePos(500, 300);
    camera->setTarget(dummy);
    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    dummySprite->setParent(dummy);
    levelDrawableLayers[0].insert(dummySprite);
    dummySprite->insertAnimation("idle", Animation(textureMap.at("dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    sword->setParent(dummy);
    levelDrawableLayers[1].insert(sword);
    sword->setTexture(textureMap.at("sword.png"));
    sword->setRelativePos(-30, 1);

    // Npc
    std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    npc->setParent(shared_from_this());
    levelBodiesSet.insert(npc);
    levelGObjectsWId[2] = npc;
    npc->setRectPixelSize(16, 16);
    npc->setRelativePos(500, 300);
    // his sprite
    std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    npcSprite->setParent(npc);
    levelDrawableLayers[0].insert(npcSprite);
    npcSprite->insertAnimation("idle", Animation(textureMap.at("dummy.png"), 16, 500, 1));
    npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<Body> platform = std::make_shared<Body>();
    platform->setParent(shared_from_this());
    levelBodiesSet.insert(platform);
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    platformSprite->setParent(platform);
    levelDrawableLayers[0].insert(platformSprite);
    platformSprite->setTexture(textureMap.at("platform.png"));

    // 2nd platform
    std::shared_ptr<Body> platform2 = std::make_shared<Body>();
    platform2->setParent(shared_from_this());
    levelBodiesSet.insert(platform2);
    platform2->setRectPixelSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    platformSprite2->setParent(platform2);
    levelDrawableLayers[0].insert(platformSprite2);
    platformSprite2->setTexture(textureMap.at("platform.png"));

    // 3rd platform
    std::shared_ptr<Body> platform3 = std::make_shared<Body>();
    platform3->setParent(shared_from_this());
    levelBodiesSet.insert(platform3);
    platform3->setRectPixelSize(100, 10);
    platform3->setRelativePos(-600, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite3 = std::make_shared<GSprite>();
    platformSprite3->setParent(platform3);
    levelDrawableLayers[0].insert(platformSprite3);
    platformSprite3->setTexture(textureMap.at("platform.png"));

    // collision grid
    std::shared_ptr<CollisionGrid> colGrid = std::make_shared<CollisionGrid>();
    std::vector<std::string> emptyColMap;
    for(unsigned i = 0; i < 60; i++){
        emptyColMap.push_back("1" + std::string(99, '0'));
    }
    colGrid->setParent(shared_from_this());
    levelBodiesSet.insert(colGrid);
    colGrid->setGrid(emptyColMap, 2);

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
    currentDialogueWeak = dialogue1;
};

// assets
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


// Necessary
// GObjects
void Level::initNecessaryGObjects(){
    // Level
    // camera
    camera = std::make_shared<Camera>();
    camera->setSize(GAME_WIDTH, GAME_HEIGHT);
    levelGObjectsSet.insert(camera);

    // Gui
    // Dialogue box
    std::shared_ptr<GSprite> dialogueBox = std::make_shared<GSprite>();
    dialogueBoxWeak = dialogueBox;
    dialogueBox->setParent(shared_from_this());
    guiDrawableLayers[0].insert(dialogueBox);
    dialogueBox->setTexture(textureMap.at("dialogueBackground.png"));
    dialogueBox->setRelativePos((GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600); // centralize it on X position
    
    // Dialogue text
    std::shared_ptr<GText> dialogueText = std::make_shared<GText>();
    dialogueTextWeak = dialogueText;
    dialogueText->setParent(dialogueBox);
    guiDrawableLayers[1].insert(dialogueText);
    dialogueText->text.setFont(fontMap["font1.ttf"]);
    dialogueText->text.setCharacterSize(30);
    dialogueText->text.setString("Hi");
    dialogueText->setRelativePos(60, 20);
};

// assets
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


// All
// Init level
void Level::init(){
    // create layers of drawables
    const u_char layersCount = 10;
    for(u_char i = 0; i < layersCount; ++i){
        guiDrawableLayers[i] = gdrawable_ptr_set();
        levelDrawableLayers[i] = gdrawable_ptr_set();
    }

    // init gui view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);

    // init object
    initNecessaryAssets();
    initNecessaryGObjects();
};