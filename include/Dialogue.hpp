#pragma once

#include <memory>
#include "GObject.hpp"

class Dialogue : public GObject
{
private:
    // Variables
    bool isLeft;
    std::unordered_set<std::shared_ptr<GObject>> characters;
    std::unordered_map<std::shared_ptr<GObject>, std::string> phraseList;

    // Methods
    // control the flow of the dialogue
    void control();

public:
    // Structors
    Dialogue();
    ~Dialogue();

    // Methods
    // update dialogue
    void update();
};
