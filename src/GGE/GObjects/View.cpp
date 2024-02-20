#include "GGE/GObjects/View.hpp"

using gge::obj::View;

// Structors
View::View(){}
View::~View(){}

// Methods
// set view center to rect center
void View::centralize(){
    view.setCenter(getRect().getPosition() + getRect().getSize()/2.f);
}

// update gobject and view pos
void View::updatePos(){
    GObject::updatePos();
    centralize();
}

// set rect and view size
void View::setRectSize(float w, float h){
    GObject::setRectSize(w, h);
    view.setSize(w, h);
    centralize();
}

// Getters
// view
const sf::View& View::getView(){
    return view;
}