#include "Level.hpp"

// Test
// GObjects
void Level::initTestGObjects(){
    ResourceManager* resourceManager = ResourceManager::getInstance();
    CollisionManager* collisionManager = CollisionManager::getInstance();

    // Level
    // dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    dummy->setParent(shared_from_this());
    collisionManager->addNewBody(dummy);
    levelGObjectsWId[1] = dummy;
    dummy->setRectPixelSize(16, 16);
    dummy->setRelativePos(500, 300);
    camera->setTarget(dummy);
    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    dummySprite->setParent(dummy);
    levelDrawableLayers[0].push_back(dummySprite);
    dummySprite->insertAnimation("idle", Animation(resourceManager->getTexture("Assets/Textures/dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    sword->setParent(dummy);
    levelDrawableLayers[1].push_back(sword);
    sword->setDoesFlipMirror(1);
    sword->setTexture(resourceManager->getTexture("Assets/Textures/sword.png"));
    sword->setRelativePos(60, 0);

    // Npc
    // std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    // npc->setParent(shared_from_this());
    // collisionManager->addNewBody(npc);
    // levelGObjectsWId[2] = npc;
    // npc->setRectPixelSize(16, 16);
    // npc->setRelativePos(500, 300);
    // // his sprite
    // std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    // npcSprite->setParent(npc);
    // levelDrawableLayers[0].push_back(npcSprite);
    // npcSprite->insertAnimation("idle", Animation(resourceManager->getTexture("Assets/Textures/dummy.png"), 16, 500, 1));
    // npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<Body> platform = std::make_shared<Body>();
    platform->setParent(shared_from_this());
    collisionManager->addNewBody(platform);
    platform->solid = 1;
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    platformSprite->setParent(platform);
    levelDrawableLayers[0].push_back(platformSprite);
    platformSprite->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));

    // 2nd platform
    std::shared_ptr<Body> platform2 = std::make_shared<Body>();
    platform2->setParent(shared_from_this());
    platform2->solid = 1;
    collisionManager->addNewBody(platform2);
    platform2->setRectPixelSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    platformSprite2->setParent(platform2);
    levelDrawableLayers[0].push_back(platformSprite2);
    platformSprite2->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));

    // 3rd platform
    std::shared_ptr<Body> platform3 = std::make_shared<Body>();
    platform3->setParent(shared_from_this());
    platform3->solid = 1;
    collisionManager->addNewBody(platform3);
    platform3->setRectPixelSize(100, 10);
    platform3->setRelativePos(-600, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite3 = std::make_shared<GSprite>();
    platformSprite3->setParent(platform3);
    levelDrawableLayers[0].push_back(platformSprite3);
    platformSprite3->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));

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

// Necessary
// GObjects
void Level::initNecessaryGObjects(){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Level
    // camera
    camera = std::make_shared<Camera>();
    camera->setSize(GAME_WIDTH, GAME_HEIGHT);

    // Gui
    // Dialogue box
    std::shared_ptr<GSprite> dialogueBox = std::make_shared<GSprite>();
    dialogueBoxWeak = dialogueBox;
    dialogueBox->setParent(shared_from_this());
    guiDrawableLayers[0].push_back(dialogueBox);
    dialogueBox->setTexture(resourceManager->getTexture("Assets/Textures/dialogueBackground.png"));
    dialogueBox->setRelativePos((GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600); // centralize it on X position
    
    // Dialogue text
    std::shared_ptr<GText> dialogueText = std::make_shared<GText>();
    dialogueTextWeak = dialogueText;
    dialogueText->setParent(dialogueBox);
    guiDrawableLayers[1].push_back(dialogueText);
    dialogueText->text.setFont(resourceManager->getFont("Assets/Fonts/font1.ttf"));
    dialogueText->text.setCharacterSize(30);
    dialogueText->text.setString("Hi");
    dialogueText->setRelativePos(60, 20);
};

// All
// Init level
void Level::init(){
    // create layers of drawables
    const int layersCount = 10;
    for(int i = 0; i < layersCount; ++i){
        levelDrawableLayers.push_back(std::vector<std::weak_ptr<GDrawable>>());
        guiDrawableLayers.push_back(std::vector<std::weak_ptr<GDrawable>>());
    }

    // init gui view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);

    // init object
    initNecessaryGObjects();
};