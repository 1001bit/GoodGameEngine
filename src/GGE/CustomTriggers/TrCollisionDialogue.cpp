#include "GGE/CustomTriggers/TrCollisionDialogue.hpp"

// Structors
TrCollisionDialogue::TrCollisionDialogue(){}
TrCollisionDialogue::~TrCollisionDialogue(){}

// Methods

void TrCollisionDialogue::doAction(){
    dialogueManager->setCurrentDialogue(dialogueId);
}

void TrCollisionDialogue::checkEvent(){
    auto body1 = body1Weak.lock();
    auto body2 = body2Weak.lock();

    if(!body1 || !body2){
        return;
    }

    if(!body1->currentRect.intersects(body2->currentRect)){
        return;
    }

    doAction();
}

void TrCollisionDialogue::setDialogue(u_char newId, DialogueManager* newDialogueManager){
    dialogueId = newId;
    dialogueManager = newDialogueManager;
}

void TrCollisionDialogue::setCollisionBodies(std::shared_ptr<KinematicBody> newBody1, std::shared_ptr<KinematicBody> newBody2){
    body1Weak = newBody1;
    body2Weak = newBody2;
}