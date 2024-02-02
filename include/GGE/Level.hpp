#pragma once

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/AnimatedSprite.hpp"
#include "GGE/GObjects/GSprite.hpp"
#include "GGE/CustomGObjects/PhysPlayer.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/GObjects/Body.hpp"
#include "GGE/CustomGObjects/TDPlayer.hpp"
#include "GGE/CustomGObjects/TDNpc.hpp"
#include "GGE/CustomGObjects/PhysNpc.hpp"
#include "GGE/GObjects/GText.hpp"
#include "GGE/GObjects/GDrawable.hpp"

#include "GGE/Dialogues/DialogueManager.hpp"

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
    // Updatable GObjects
    std::vector<std::weak_ptr<GObject>> updatableGObjects;

    // Level GObjects
    // Drawable
    std::vector< std::vector<std::weak_ptr<GDrawable>> > levelDrawableLayers;
    // With own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> levelGObjectsWId;
    // Game camera that is following some GObject
    std::shared_ptr<Camera> camera;

    // GUI GObjects
    // Layers of drawables
    std::vector< std::vector<std::weak_ptr<GDrawable>> > guiDrawableLayers;
    // Dialogue manager
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