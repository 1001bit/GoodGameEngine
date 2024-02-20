#pragma once

#include <unordered_map>
#include "GGECustom/Dialogues/Dialogue.hpp"
#include "GGE/GObjects/Text.hpp"
#include "GGE/GObjects/Sprite.hpp"
#include "GGECustom/GObjects/SmoothFollower.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "GGECustom/GameConstants.hpp"
#include "GGE/Level.hpp"

namespace gge {

class DialogueManager : public gge::obj::GObject
{
private:
    // Variables
    // all the dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialoguesMap;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;

    // dialogue box sprite
    std::weak_ptr<obj::Sprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<obj::Text> dialogueTextWeak;

public:
    // Structors
    DialogueManager();
    ~DialogueManager();

    // Needed gobjects
    std::weak_ptr<Level> levelWeak;
    std::weak_ptr<obj::SmoothFollower> cameraWeak;

    // Methods
    // Init drawable part
    void initDrawables();
    // Set all the dialogues list
    void setDialoguesMap(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues);

    // Update current dialogue
    void update(const float& dTimeMs);
    // Set current dialogue with id
    void startDialogue(u_char id);
    // Hide or show drawable part
    void setDrawableVisiblity(bool visible);
};

}