#pragma once

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/AnimatedSprite.hpp"
#include "GGE/GObjects/GSprite.hpp"
#include "GGE/GObjects/PhysPlayer.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/GObjects/Body.hpp"
#include "GGE/GObjects/TDPlayer.hpp"
#include "GGE/GObjects/TDNpc.hpp"
#include "GGE/GObjects/PhysNpc.hpp"
#include "GGE/GObjects/GText.hpp"
#include "GGE/GObjects/GDrawable.hpp"

#include "GGE/Level/DialogueManager.hpp"

#include "GGE/SingletonManagers/ResourceManager.hpp"
#include "GGE/SingletonManagers/PhysicsManager.hpp"

#include "GGE/GameConstants.hpp"

// #define DRAWCOLLIDER

class Level : public GObject
{
private:
    // Gui
    sf::View guiView;

    // Data init patterns
    void initNecessaryGObjects();
    
public:
    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Drawable Level GObjects
    std::vector< std::vector<std::weak_ptr<GDrawable>> > levelDrawableLayers;
    // Level GObjects with own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> levelGObjectsWId;
    // Game camera that is following some GObject
    std::shared_ptr<Camera> camera;

    // GUI GObjects
    // layers of drawable GUI GObjects
    std::vector< std::vector<std::weak_ptr<GDrawable>> > guiDrawableLayers;
    // dialogue manager
    DialogueManager dialogueManager;
    ///////////////////////////

    // Methods
    // Init level
    void init();
    // Load level from file
    void loadFromFile(const sf::String& fileName);

    // Update states of all the objects
    void update(const float& dTimeMs);
    // Draw drawable objects
    void drawGObjetcs(sf::RenderWindow& window);
};