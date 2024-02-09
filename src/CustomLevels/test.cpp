#include "inits.hpp"

void testInit(std::shared_ptr<Level> level){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Level
    // dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    dummy->setNewParent(level);
    level->physicsManager.addNewKinematicBody(dummy);
    level->levelGObjectsWId[1] = dummy;
    dummy->setRectPixelSize(16, 16);
    dummy->setCurrentPosition({000, 300});
    level->camera->setTarget(dummy);
    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    dummySprite->setNewParent(dummy);
    level->levelDrawableLayers[1].push_back(dummySprite);
    level->updatableGObjects.push_back(dummySprite);  
    dummySprite->insertAnimation("idle", Animation(resourceManager->getTexture("Assets/Textures/dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    sword->setNewParent(dummy);
    level->levelDrawableLayers[2].push_back(sword);
    sword->setTexture(resourceManager->getTexture("Assets/Textures/sword.png"));
    sword->setRelativePos({60, 0});
    sword->makeFlippable();

    // Npc
    std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    npc->setNewParent(level);
    level->physicsManager.addNewKinematicBody(npc);
    level->levelGObjectsWId[2] = npc;
    npc->setRectPixelSize(16, 16);
    npc->setCurrentPosition({500, 300});
    // his sprite
    std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    npcSprite->setNewParent(npc);
    level->levelDrawableLayers[0].push_back(npcSprite);
    level->updatableGObjects.push_back(npcSprite);  
    npcSprite->insertAnimation("idle", Animation(resourceManager->getTexture("Assets/Textures/dummy.png"), 16, 500, 1));
    npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<Body> platform = std::make_shared<Body>();
    platform->setNewParent(level);
    level->physicsManager.addNewSolidBody(platform);
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos({800, 730});
    // it's sprite
    std::shared_ptr<GSprite>  platformSprite = std::make_shared<GSprite>();
    platformSprite->setNewParent(platform);
    level->levelDrawableLayers[0].push_back(platformSprite);
    platformSprite->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));

    // a platform
    platform = std::make_shared<Body>();
    platform->setNewParent(level);
    level->physicsManager.addNewSolidBody(platform);
    platform->setRectPixelSize(100, 10);
    platform->setRelativePos({100, 800});
    // it's sprite
    platformSprite = std::make_shared<GSprite>();
    platformSprite->setNewParent(platform);
    level->levelDrawableLayers[0].push_back(platformSprite);
    platformSprite->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));

    // bunch of platforms
    for(int i = 0; i < 1000; ++i){
        // a platform
        platform = std::make_shared<Body>();
        platform->setNewParent(level);
        level->physicsManager.addNewSolidBody(platform);
        platform->setRectPixelSize(100, 10);
        platform->setRelativePos({-600.f - 700.f*i, 730.f});
        // it's sprite
        platformSprite = std::make_shared<GSprite>();
        platformSprite->setNewParent(platform);
        level->levelDrawableLayers[0].push_back(platformSprite);
        platformSprite->setTexture(resourceManager->getTexture("Assets/Textures/platform.png"));
    }

    // Gui
    // dummy-npc dialogue
    std::shared_ptr<Dialogue> dialogue1 = std::make_shared<Dialogue>();
    level->dialogueManager.setDialoguesMap({{0, dialogue1}});
    dialogue1->setLines({
        {1, "hello"},
        {2, "hi"},
        {1, "bye"},
        {2, "goodbye"}
    });

    // Instructions
    // start dialogue on collision of player and npc
    std::shared_ptr<TrCollision> trigger = std::make_shared<TrCollision>();
    trigger->setCollisionBodies(npc, dummy);
    std::shared_ptr<AcDialogue> action = std::make_shared<AcDialogue>();
    action->setDialogueParams(0, &level->dialogueManager);
    trigger->setAction(action);

    level->triggersManager.addNewTrigger(trigger);
}