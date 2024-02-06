#include "GGE/CustomInstruction/AcDialogue.hpp"

// Structors
AcDialogue::AcDialogue(){}
AcDialogue::~AcDialogue(){}

// Methods

void AcDialogue::doAction(){
    dialogueManager->startDialogue(dialogueId);
}

void AcDialogue::setDialogueParams(u_char newId, DialogueManager* newDialogueManager){
    dialogueId = newId;
    dialogueManager = newDialogueManager;
}