#include "GGE/Game.hpp"

#include "CustomLevels/inits.hpp"

void initControls(){
    ControlsManager* controlsManager = ControlsManager::getInstance();
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
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "GoodGame test", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);

    // init the game
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->init();
    initControls();

    // init levels
    std::shared_ptr<Level> level = game->currentLevel;
    necessaryInit(level);
    testInit(level);

    // start the main loop
    game->loop(window);

    return 0;
}