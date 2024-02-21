#pragma once

#include <memory>
#include "GGE/Controls/ControlsManager.hpp"
#include "GGE/Gobjects/Gobject.hpp"

namespace gge {

struct DialogueLine {
    int16_t characterId;
    std::string line;
};

class Dialogue
{
private:
    // Variables
    // vector of participant id and their line
    std::vector<DialogueLine> linesList;
    // id of current dialogueLine
    int16_t currentDialogueLineId;

    // Methods
    // control the flow of the dialogue
    void control();

public:
    // Structors
    Dialogue();
    ~Dialogue();

    // Methods
    // add a new participant
    void addParticipant(uint16_t id, std::shared_ptr<obj::Gobject> pointer);
    // set new lines list
    void setLines(std::vector<DialogueLine> newLines);
    // update dialogue
    void update();

    // Getters
    // Get current line from number
    const DialogueLine& getCurrentLine();
};

}