#pragma once

#include "GGE/Gobjects/Gobject.hpp"

namespace gge {

struct DialogueLine {
    int16_t characterId;
    std::string line;
};

class Dialogue
{
private:
    // vector of participant id and their line
    std::vector<DialogueLine> linesList;
    // id of current dialogueLine
    short currentDialogueLineId;

    // Methods
    // control the flow of the dialogue
    void control();

public:
    // Structors
    Dialogue();
    ~Dialogue();

    // Methods
    // add a new participant
    void addParticipant(ushort id, std::shared_ptr<obj::Gobject> pointer);
    // set new lines list
    void setLines(std::vector<DialogueLine> newLines);
    // update dialogue
    void update();

    // Getters
    // linesList[currentDialogueLineId]
    const DialogueLine& getCurrentLine();
};

}