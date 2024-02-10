#pragma once

#include "GGE/Instructions/Trigger.hpp"
#include "GGE/GObjects/KinematicBody.hpp"
#include "GGE/Dialogues/DialogueManager.hpp"

// Some random trigger
class TrCollision : public gge::Trigger
{
private:
    // Variables
    std::weak_ptr<gge::KinematicBody> body1Weak;
    std::weak_ptr<gge::KinematicBody> body2Weak;

public:
    // Structors
    TrCollision();
    ~TrCollision();

    // Methods
    // checks if some bodies collided
    void checkEvent();
    // Set 2 bodies
    void setCollisionBodies(std::shared_ptr<gge::KinematicBody> newBody1, std::shared_ptr<gge::KinematicBody> newBody2);
};