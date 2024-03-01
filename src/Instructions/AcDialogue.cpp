 #include "Instructions/AcDialogue.hpp"

using gge::ins::AcDialogue;

// Structors
AcDialogue::AcDialogue(){}
AcDialogue::~AcDialogue(){}

// Methods
// start dialogue
void AcDialogue::activate(){
    if(auto dialogueManager = dialogueManagerWeak.lock()){
        dialogueManager->startDialogue(dialogueId);
    }
}

// set dialogue id and it's manager
void AcDialogue::setDialogueParams(u_char newId, std::shared_ptr<gge::DialogueManager> dialogueManager){
    dialogueId = newId;
    dialogueManagerWeak = dialogueManager;
}