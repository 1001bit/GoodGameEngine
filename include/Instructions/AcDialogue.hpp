#pragma once

#include "GGE/Instructions/Action.hpp"
#include "Dialogues/DialogueManager.hpp"

namespace gge::ins {

class AcDialogue : public Action
{
private:
    u_char dialogueId;
    std::weak_ptr<gge::DialogueManager> dialogueManagerWeak;

public:
    // Structors
    AcDialogue();
    ~AcDialogue();

    // Methods
    // set dialogueId, dialogueManager
    void setDialogueParams(u_char newId, std::shared_ptr<gge::DialogueManager> dialogueManager);
    // start dialogue
    void activate();
};

}