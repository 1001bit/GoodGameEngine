#include "inits.hpp"

#include "GGECustom/Gobjects/PhysNpc.hpp"
#include "GGECustom/Gobjects/PhysPlayer.hpp"
#include "GGE/Gobjects/AnimatedSprite.hpp"
#include "GGECustom/Instructions/AcDialogue.hpp"
#include "GGECustom/Instructions/TrCollision.hpp"

using namespace gge;

std::shared_ptr<gge::Level> clvl::newTest(){
    std::shared_ptr<Level> level = std::make_shared<Level>();
    level->init();

    // Level
    // Smooth following camera
    std::shared_ptr<obj::SmoothFollower> camera = std::make_shared<obj::SmoothFollower>();
    level->addChild(camera);
    if(auto levelView = level->levelViewWeak.lock()){
        camera->addChild(levelView);
        levelView->setRelativePos(levelView->getRect().getSize() / -2.f);
    }
    level->updatableGobjects.push_back(camera);

    // dummy
    std::shared_ptr<obj::PhysPlayer> dummy = std::make_shared<obj::PhysPlayer>();
    level->addChild(dummy);
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(dummy));
    level->gobjectIdMap[1] = dummy;
    dummy->setRectPixelSize(16, 16);
    dummy->setCurrentPos({000, 300});
    camera->setTarget(dummy);
    
    // his sprite
    std::shared_ptr<obj::AnimatedSprite> dummySprite = std::make_shared<obj::AnimatedSprite>();
    dummy->addChild(dummySprite);
    level->drawablesManager.newDrawable(dummySprite, false, 1);
    level->updatableGobjects.push_back(dummySprite);  
    dummySprite->insertAnimation("idle", Animation(level->resourceManager.getTexture("Assets/Textures/dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // his sword
    std::shared_ptr<obj::Sprite> sword = std::make_shared<obj::Sprite>();
    dummy->addChild(sword);
    level->drawablesManager.newDrawable(sword, false, 2);
    sword->setTexture(level->resourceManager.getTexture("Assets/Textures/sword.png"));
    sword->setRelativePos({60, 0});
    sword->makeFlippable();

    // Npc
    std::shared_ptr<obj::PhysNpc> npc = std::make_shared<obj::PhysNpc>();
    level->addChild(npc);
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(npc));
    level->gobjectIdMap[2] = npc;
    npc->setRectPixelSize(16, 16);
    npc->setCurrentPos({500, 300});
    npc->initCooldowns(level->cooldownsManager);
    // his sprite
    std::shared_ptr<obj::AnimatedSprite> npcSprite = std::make_shared<obj::AnimatedSprite>();
    npc->addChild(npcSprite);
    level->drawablesManager.newDrawable(npcSprite, false, 0);
    level->updatableGobjects.push_back(npcSprite);  
    npcSprite->insertAnimation("idle", Animation(level->resourceManager.getTexture("Assets/Textures/dummy.png"), 16, 100, 1));
    npcSprite->playAnimation("idle");
    // his sword
    sword = std::make_shared<obj::Sprite>();
    npc->addChild(sword);
    level->drawablesManager.newDrawable(sword, false, 1);
    sword->setTexture(level->resourceManager.getTexture("Assets/Textures/sword.png"));
    sword->setRelativePos({60, 0});
    sword->makeFlippable();

    // a platform
    std::shared_ptr<obj::Body> platform = std::make_shared<obj::Body>();
    level->addChild(platform);
    level->physicsManager.addNewBody(platform);
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos({800, 730});
    // it's sprite
    std::shared_ptr<obj::Sprite>  platformSprite = std::make_shared<obj::Sprite>();
    platform->addChild(platformSprite);
    level->drawablesManager.newDrawable(platformSprite, false, 0);
    platformSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/platform.png"));

    // a platform
    platform = std::make_shared<obj::Body>();
    level->addChild(platform);
    level->physicsManager.addNewBody(platform);
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos({100, 800});
    // it's sprite
    platformSprite = std::make_shared<obj::Sprite>();
    platform->addChild(platformSprite);
    level->drawablesManager.newDrawable(platformSprite, false, 0);
    platformSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/platform.png"));

    // bunch of platforms
    for(int i = 0; i < 100; ++i){
        // a platform
        platform = std::make_shared<obj::Body>();
        level->addChild(platform);
        level->physicsManager.addNewBody(platform);
        platform->setRectPixelSize(100, 10);
        platform->setRelativePos({-600.f - 700.f*i, 730.f});
        // it's sprite
        platformSprite = std::make_shared<obj::Sprite>();
        platform->addChild(platformSprite);
        level->drawablesManager.newDrawable(platformSprite, false, 0);
        platformSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/platform.png"));
    }

    // Gui
    // Dialogue manager
    std::shared_ptr<gge::DialogueManager> dialogueManager = std::make_shared<gge::DialogueManager>();
    level->addChild(dialogueManager);
    level->updatableGobjects.push_back(dialogueManager);
    dialogueManager->levelWeak = level;
    dialogueManager->cameraWeak = camera;
    dialogueManager->initDrawables();

    // dummy-npc dialogue
    std::shared_ptr<Dialogue> dialogue1 = std::make_shared<Dialogue>();
    dialogueManager->setDialoguesMap({{0, dialogue1}});
    dialogue1->setLines({
        {1, "hello"},
        {2, "hi"},
        {1, "bye"},
        {2, "goodbye"}
    });

    // Instructions
    // start dialogue on collision of player and npc
    std::shared_ptr<ins::TrCollision> trigger = std::make_shared<ins::TrCollision>();
    trigger->setCollisionBodies(npc, dummy);

    std::shared_ptr<ins::AcDialogue> action = std::make_shared<ins::AcDialogue>();
    action->setDialogueParams(0, dialogueManager);
    trigger->setAction(action);

    level->triggersManager.addNewTrigger(trigger);
    
    return level;
}