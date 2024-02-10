#include "GGE/CustomInstructions/TrCollision.hpp"

// Structors
TrCollision::TrCollision(){}
TrCollision::~TrCollision(){}

// Methods

void TrCollision::checkEvent(){
    if(!active){
        return;
    }

    auto body1 = body1Weak.lock();
    auto body2 = body2Weak.lock();

    if(!body1 || !body2){
        return;
    }

    if(!body1->currentRect.intersects(body2->currentRect)){
        return;
    }

    action->doAction();

    active = 0;
}

void TrCollision::setCollisionBodies(std::shared_ptr<gge::KinematicBody> newBody1, std::shared_ptr<gge::KinematicBody> newBody2){
    body1Weak = newBody1;
    body2Weak = newBody2;
}