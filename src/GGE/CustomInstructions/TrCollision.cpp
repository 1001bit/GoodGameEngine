#include "GGE/CustomInstruction/TrCollision.hpp"

// Structors
TrCollision::TrCollision(){}
TrCollision::~TrCollision(){}

// Methods

void TrCollision::checkEvent(){
    auto body1 = body1Weak.lock();
    auto body2 = body2Weak.lock();

    if(!body1 || !body2){
        return;
    }

    if(!body1->currentRect.intersects(body2->currentRect)){
        return;
    }

    action->doAction();
}

void TrCollision::setCollisionBodies(std::shared_ptr<KinematicBody> newBody1, std::shared_ptr<KinematicBody> newBody2){
    body1Weak = newBody1;
    body2Weak = newBody2;
}