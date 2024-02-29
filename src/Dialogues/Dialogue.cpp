#include "Dialogues/Dialogue.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::Dialogue;

// Structors
Dialogue::Dialogue(){
    currentDialogueLineId = 1;
}

Dialogue::~Dialogue(){}

// Methods
// update the dialogue 
void Dialogue::update(){
    // restart the dialogue if it may be played again
    if(currentDialogueLineId == 0){
        currentDialogueLineId = 1;
    }
    control();
}

// control the flow of the dialogue
void Dialogue::control(){
    ControlsManager* controlsManager = ControlsManager::getInstance();
    if(controlsManager->isPressed("dialogueNext")){
        currentDialogueLineId += 1;
        if(currentDialogueLineId >= short(linesList.size())){
            currentDialogueLineId = 0;
        }
    }
}

// set new lines list
void Dialogue::setLines(std::vector<DialogueLine> newLines){
    linesList = newLines;
    linesList.insert(linesList.begin(), {1, ""});
}

// Getters
// get current line
const gge::DialogueLine& Dialogue::getCurrentLine(){
    return linesList[currentDialogueLineId];
}