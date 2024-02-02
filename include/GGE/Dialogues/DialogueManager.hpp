#pragma once

#include <unordered_map>
#include "GGE/Dialogues/Dialogue.hpp"
#include "GGE/GObjects/GText.hpp"
#include "GGE/GObjects/GSprite.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/SingletonManagers/ResourceManager.hpp"
#include "GGE/GameConstants.hpp"

class DialogueManager
{
private:
    // Variables
    // all the dialogues
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;

    // dialogue box
    std::weak_ptr<GSprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<GText> dialogueTextWeak;

public:
    // Structors
    DialogueManager();
    ~DialogueManager();

    // Methods
    // Init drawable part
    void initDrawables(std::shared_ptr<GSprite> newDialogueBox, std::shared_ptr<GText> newDialogueText);
    // Set all the dialogues list
    void setDialogues(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues);
    // Update current dialogue
    void updateCurrentDialogue(std::unordered_map<uint16_t, std::weak_ptr<GObject>>& levelGObjectsWId, std::shared_ptr<Camera> camera);
    // Set current dialogue with id
    void setCurrentDialogue(u_char id);
};