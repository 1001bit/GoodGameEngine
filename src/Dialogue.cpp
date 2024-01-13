#include "Dialogue.hpp"

// Structors
Dialogue::Dialogue(){
    currentLineId = 1;
    isRepeatable = 0;
}

Dialogue::~Dialogue(){}

// Methods
// update the dialogue 
void Dialogue::update(){
    // restart the dialogue if it may be played again
    if(currentLineId == 0 && isRepeatable){
        currentLineId = 1;
    }
    control();
}

// control the flow of the dialogue
void Dialogue::control(){
    ControlsManager* control = ControlsManager::getInstance();
    if(control->isControlPressedOnce("dialogueNext")){
        currentLineId += 1;
        if(currentLineId >= linesList.size()){
            currentLineId = 0;
        }
    }
}

// make the dialogue repeatable
void Dialogue::makeRepeatable(){
    isRepeatable = 1;
}

// add a new participant
void Dialogue::addParticipant(uint16_t id, std::shared_ptr<GObject> pointer){
    participantsList.insert({id, pointer});
}

// set new lines list
void Dialogue::setLines(std::vector<DialogueLine> newLines){
    linesList = newLines;
    linesList.insert(linesList.begin(), {0, ""});
}

// Getters
// get current line
const DialogueLine& Dialogue::getCurrentLine(){
    return linesList[currentLineId];
}