#pragma once

#include "Dialogues/Dialogue.hpp"
#include "GGE/Gobjects/Text.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "Gobjects/SmoothFollower.hpp"
#include "GGE/Level/Level.hpp"

namespace gge {
    
class DialogueManager : public gge::obj::Gobject
{
private:
    // all the dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialoguesMap;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;

    // dialogue box sprite
    std::weak_ptr<obj::Sprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<obj::Text> dialogueTextWeak;

    // level and camera
    std::weak_ptr<Level> levelWeak;
    std::weak_ptr<obj::SmoothFollower> cameraWeak;

public:
    // Structors
    DialogueManager(std::weak_ptr<Level> level, std::weak_ptr<obj::SmoothFollower> camera);
    ~DialogueManager();

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