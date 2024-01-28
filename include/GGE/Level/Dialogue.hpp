#pragma once

#include <memory>
#include "GGE/GObjects/GObject.hpp"

struct DialogueLine {
    u_char characterId;
    std::string line;
};

class Dialogue
{
private:
    // Variables
    // participant id and their line
    std::vector<DialogueLine> linesList;
    // current line
    int16_t currentLineId;

    // Methods
    // control the flow of the dialogue
    void control();

public:
    // Structors
    Dialogue();
    ~Dialogue();

    // Methods
    // add a new participant
    void addParticipant(uint16_t id, std::shared_ptr<GObject> pointer);
    // set new lines list
    void setLines(std::vector<DialogueLine> newLines);
    // update dialogue
    void update();

    // Getters
    // Get current line from number
    const DialogueLine& getCurrentLine();
};
