#include "GGE/Game.hpp"

int main()
{
    srand(time(NULL));

    // init window
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "GoodGame test", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);

    // init the game
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->init();

    // start the main loop
    game->loop(window);

    return 0;
}