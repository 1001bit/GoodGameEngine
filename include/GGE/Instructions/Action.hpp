#pragma once

class Action
{
private:

public:
    // Structors
    Action();
    ~Action();

    // Do action of trigger if event has happened
    virtual void doAction();
};
