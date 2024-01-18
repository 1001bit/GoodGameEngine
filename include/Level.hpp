#pragma once

#include "GObject.hpp"
#include "AnimatedSprite.hpp"
#include "GSprite.hpp"
#include "PhysPlayer.hpp"
#include "Camera.hpp"
#include "Body.hpp"
#include "TDPlayer.hpp"
#include "TDNpc.hpp"
#include "PhysNpc.hpp"
#include "GText.hpp"
#include "Dialogue.hpp"
#include "GDrawable.hpp"

// Set of GObjects
typedef std::unordered_set<std::shared_ptr<GDrawable>> gdrawable_ptr_set;
typedef std::unordered_set<std::shared_ptr<Body>> body_ptr_set;
typedef std::unordered_set<std::shared_ptr<GObject>> gobject_ptr_set;

// sizes of the game
constexpr uint GAME_WIDTH = 1440;
constexpr uint GAME_HEIGHT = 880;

class Level : public GObject
{
private:
    // Level GObjects
    // Layers of drawable objects
    std::map<u_char, gdrawable_ptr_set> levelDrawableLayers;
    // Set of body objects
    body_ptr_set levelBodiesSet;
    // Set of other objects
    gobject_ptr_set levelGObjectsSet;
    // set of level GObjects with own id
    std::unordered_map<uint16_t, std::weak_ptr<GObject>> levelGObjectsWId;

    // GUI GObjects
    // layers of drawable GUI GObjects
    std::map<u_char, gdrawable_ptr_set> guiDrawableLayers;
    // set of dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialogues;

    // Storages
    // storage of the textures
    std::unordered_map<std::string, sf::Texture> textureMap;
    // storage of the fonts
    std::unordered_map<std::string, sf::Font> fontMap;

    // Necessary GObjects
    // game camera that is following some GObject
    std::shared_ptr<Camera> camera;
    // dialogue box
    std::weak_ptr<GSprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<GText> dialogueTextWeak;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;
    // gui view
    sf::View guiView;

    // Updates
    // Update all the GObjects of the level
    void updateLevelObjects(sf::RenderWindow& window, const float& timeMs);
    // Update all the GObjects of the GUI
    void updateGuiObjects(sf::RenderWindow& window, const float& timeMs);

    // Data init patterns
    void initNecessaryGObjects();
    void initNecessaryAssets();
    
public:
    // Structors
    Level();
    ~Level();

    // Methods
    // Init level
    void init();
    // Update states of all the objects
    void update(sf::RenderWindow& window, const float& timeMs);
    // Load level from file
    void loadFromFile(const sf::String& fileName);

    // test inits
    void initTestGObjects();
    void initTestAssets();
};