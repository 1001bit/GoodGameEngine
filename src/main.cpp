#include "GGE/Game.hpp"
#include "Levels/inits.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGE/Controls/ControlsManager.hpp"

const float gge::obj::Sprite::SPRITE_SCALE = 7;

void initControls(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();
    // Keyboard controls
    controlsManager->setControlsMap({
        { "wLeft", {{sf::Keyboard::A}, {}} },
        { "wRight", {{sf::Keyboard::D}, {}} },
        { "wUp", {{sf::Keyboard::W}, {}} },
        { "wDown", {{sf::Keyboard::S}, {}} },
        { "jump", {{sf::Keyboard::Space}, {}} },
        { "dialogueNext", {{}, {sf::Mouse::Left}} }
    });
}

int main()
{
    srand(time(NULL));

    // init the game
    gge::Game game = gge::Game();
    initControls();

    // init levels
    game.levelsManager.makeLevelByFunc(0, clvl::newTest);

    // start level
    game.levelsManager.setCurrentLevel(0);

    // start the main loop
    game.loop(1280, 720, 150, 120, "GGE test");

    return 0;
}