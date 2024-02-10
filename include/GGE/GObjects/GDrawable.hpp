#pragma once

#include "GObject.hpp"

namespace gge {

class GDrawable : public GObject
{
private:
    
public:
    // Structors
    GDrawable();
    ~GDrawable();

    // Methods
    // draw self drawable object
    virtual void drawSelf(sf::RenderWindow& window);
};

}