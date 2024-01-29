#include "GGE/Dialogues/DialogueManager.hpp"

// Structors
DialogueManager::DialogueManager(){}
DialogueManager::~DialogueManager(){}

// Methods
// Init drawable part
void DialogueManager::initDrawables(std::shared_ptr<GSprite> newDialogueBox, std::shared_ptr<GText> newDialogueText){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Dialogue box
    dialogueBoxWeak = newDialogueBox;
    newDialogueBox->setTexture(resourceManager->getTexture("Assets/Textures/dialogueBackground.png"));
    newDialogueBox->setRelativePos((GAME_WIDTH-(newDialogueBox->sprite.getGlobalBounds().width))/2, 600); // centralize it on X position
    
    // Dialogue text
    dialogueTextWeak = newDialogueText;
    newDialogueText->text.setFont(resourceManager->getFont("Assets/Fonts/font1.ttf"));
    newDialogueText->text.setCharacterSize(30);
    newDialogueText->text.setString("Hi");
    newDialogueText->setRelativePos(60, 20);
}

// Set all the dialogues list
void DialogueManager::setDialogues(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues){
    dialogues = newDialogues;
}

// Set current dialogue with id
void DialogueManager::setCurrentDialogue(u_char id){
    if(!dialogues.count(id)){
        return;
    }
    currentDialogueWeak = dialogues.at(id);
}

// Update current dialogue
void DialogueManager::updateCurrentDialogue(){
    // if current dialogue is active
    auto currentDialogue = currentDialogueWeak.lock();
    if(!currentDialogue){
        return;
    }

    currentDialogue->update();

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

// Getters
// Who reads the line now
const u_char DialogueManager::getCurrentSpeakerId(){
    auto currentDialogue = currentDialogueWeak.lock();
    if(!currentDialogue){
        return 0;
    }
    return currentDialogue->getCurrentLine().characterId;
}