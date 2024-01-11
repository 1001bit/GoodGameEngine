#include "Dialogue.hpp"

// Structors
Dialogue::Dialogue(){}

Dialogue::~Dialogue(){}

// Methods
// update the dialogue 
void Dialogue::update(){
    control();
}

// control the flow of the dialogue
void Dialogue::control(){
    
}

// add a new participant
void Dialogue::addParticipant(u_char id, std::shared_ptr<GObject> pointer){
    participantsList.insert({id, pointer});
}

// set new lines list
void Dialogue::setLines(std::vector<std::pair<u_char, std::string>> newLines){
    linesList = newLines;
}