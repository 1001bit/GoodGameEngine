#pragma once

#include "GGE/Triggers/Trigger.hpp"
#include "GGE/GObjects/KinematicBody.hpp"
#include "GGE/Dialogues/DialogueManager.hpp"

// Some random trigger
class TrCollisionDialogue : public Trigger
{
private:
    // Variables
    std::weak_ptr<KinematicBody> body1Weak;
    std::weak_ptr<KinematicBody> body2Weak;
    u_char dialogueId;
    DialogueManager* dialogueManager;

    // Methods
    // start dialogue
    void doAction();

public:
    // Structors
    TrCollisionDialogue();
    ~TrCollisionDialogue();

    // Methods
    // checks if some bodies collided
    void checkEvent();

    void setDialogue(u_char newId, DialogueManager* newDialogueManager);
    void setCollisionBodies(std::shared_ptr<KinematicBody> newBody1, std::shared_ptr<KinematicBody> newBody2);
};