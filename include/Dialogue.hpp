#pragma once

#include <memory>
#include "GObject.hpp"

/*
How dialogue participants are chosen:
- Upon creating a level in level editor, creator may pick an ID for any GObject.
- When level is loaded into the game, level loader iterates through each object. 
- If it sees a GObject with id provided, it adds it to a map similar to particiapnts.
- When dialogues are created, they pick values from that map.
*/

/*
How dialogues are shown:
- There is a single dialogue shower "visibleDialogue" object (just a group of sprites, text, etc.)
- There is a pointer "currentDialogue" that refers to current Dialogue object
- If currentDialogue is null, visibleDialogue is hidden.
- If currentDialogue isn't null, visibleDialogue gets all the information about it and shows it.
*/

class Dialogue : public GObject
{
private:
    // Variables
    // participant id and pointer
    std::unordered_map<u_char, std::shared_ptr<GObject>> participantsList;
    // participant id and their line
    std::vector<std::pair<u_char, std::string>> linesList;
    // current line
    uint currentLineId;

    // Methods
    // control the flow of the dialogue
    void control();

public:
    // Structors
    Dialogue();
    ~Dialogue();

    // Methods
    // add a new participant
    void addParticipant(u_char id, std::shared_ptr<GObject> pointer);
    // set new lines list
    void setLines(std::vector<std::pair<u_char, std::string>> newLines);
    // update dialogue
    void update();

    // Getters

    const std::pair<u_char, std::string>& getCurrentLine();
};
