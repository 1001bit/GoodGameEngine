#include "GGE/Game.hpp"
#include "GGECustom/Levels/inits.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGECustom/GameConstants.hpp"

void initControls(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();
    // Keyboard controls
    controlsManager->setKeyboardControlsMap({
        {"wLeft", sf::Keyboard::A},
        {"wRight", sf::Keyboard::D},
        {"wUp", sf::Keyboard::W},
        {"wDown", sf::Keyboard::S},
        {"jump", sf::Keyboard::Space},
    });
    // mouse controls
    controlsManager->setMouseControlsMap({
        {"dialogueNext", sf::Mouse::Left}
    });
}

int main()
{
    srand(time(NULL));

    // init window
    sf::RenderWindow window(sf::VideoMode(gge::GAME_WIDTH, gge::GAME_HEIGHT), "GoodGame test", sf::Style::Close);
    window.setFramerateLimit(gge::MAX_FPS);

    // init the game
    gge::Game game = gge::Game();
    initControls();

    // init levels
    game.currentLevel = clvl::newTest();

    // start the main loop
    game.loop(window);

    return 0;
}