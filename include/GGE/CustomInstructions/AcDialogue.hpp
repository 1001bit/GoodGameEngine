#pragma once

#include "GGE/Instructions/Action.hpp"
#include "GGE/Dialogues/DialogueManager.hpp"

class AcDialogue : public Action
{
private:
    // Variables
    u_char dialogueId;
    DialogueManager* dialogueManager;

public:
    // Structors
    AcDialogue();
    ~AcDialogue();

    // Methods
    // set dialogueId, dialogueManager
    void setDialogueParams(u_char newId, DialogueManager* newDialogueManager);
    // start dialogue
    void doAction();
};