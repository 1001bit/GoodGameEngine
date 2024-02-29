 #include "Dialogues/DialogueManager.hpp"
 #include "GameConstants.hpp"

using gge::DialogueManager;

// Structors
DialogueManager::DialogueManager(std::weak_ptr<Level> level, std::weak_ptr<obj::SmoothFollower> camera) : levelWeak(level), cameraWeak(camera){}
DialogueManager::~DialogueManager(){}

// Methods
// Init drawable part
void DialogueManager::initDrawables(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    // Dialogue box
    std::shared_ptr<obj::Sprite> dialogueBox = std::make_shared<obj::Sprite>();
    level->drawablesManager.newDrawable(dialogueBox, true, 0);
    level->addChild(dialogueBox);
    dialogueBoxWeak = dialogueBox;

    dialogueBox->setTexture(level->resourceManager.getTexture("Assets/Textures/dialogueBackground.png"));
    
    // Dialogue text
    std::shared_ptr<obj::Text> dialogueText = std::make_shared<obj::Text>();
    level->drawablesManager.newDrawable(dialogueText, true, 1);
    dialogueBox->addChild(dialogueText);
    dialogueTextWeak = dialogueText;

    dialogueText->text.setFont(level->resourceManager.getFont("Assets/Fonts/font1.ttf"));
    dialogueText->text.setCharacterSize(30);
    dialogueText->text.setString("...");
    dialogueText->setRelativePos({60, 20});

    setDrawableVisiblity(0);
}

// Set all the dialogues list
void DialogueManager::setDialoguesMap(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues){
    dialoguesMap = newDialogues;
}

// Set current dialogue with id
void DialogueManager::startDialogue(u_char id){
    if(!dialoguesMap.count(id)){
        return;
    }
    setDrawableVisiblity(1);
    currentDialogueWeak = dialoguesMap.at(id);
}

// Update current dialogue
void DialogueManager::update(const float&){
    // if current dialogue is active
    auto currentDialogue = currentDialogueWeak.lock();
    if(!currentDialogue){
        return;
    }
    currentDialogue->update();

    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    // set dialogue text
    if(auto dialogueText = dialogueTextWeak.lock()){
        dialogueText->text.setString(currentDialogue->getCurrentLine().line);
    }

    // set camera target
    if(auto camera = cameraWeak.lock()){
        ushort speakerId = currentDialogue->getCurrentLine().characterId;
        std::shared_ptr<obj::Gobject> currentSpeaker = level->gobjectIdMap.at(1).lock();
        // if speaker's id is in IDs map
        if(level->gobjectIdMap.count(speakerId)){
            currentSpeaker = level->gobjectIdMap.at(speakerId).lock();
            // if speaker object is deleted - remove it from map
            if(!currentSpeaker){
                level->gobjectIdMap.erase(speakerId);
            }
        }
        camera->setTarget(currentSpeaker);
    }

    // if empty string (after last line) - stop dialogue
    if(currentDialogue->getCurrentLine().line == ""){
        currentDialogueWeak.reset();
        setDrawableVisiblity(0);
    }
}

// Hide or show drawable part
void DialogueManager::setDrawableVisiblity(bool visible){
    if(auto dialogueBox = dialogueBoxWeak.lock()){
        if(visible){
            dialogueBox->setRelativePos({(GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600}); // centralize it on X position
        } else {
            dialogueBox->setRelativePos({9999, 9999});
        }
    }
}