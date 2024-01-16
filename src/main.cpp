#include <SFML/Graphics.hpp>
#include "Game.hpp"

// Max framerate
constexpr unsigned FPS = 120;

int main()
{
    srand(time(NULL));

    // init window
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "GoodGame test", sf::Style::Close);
    window.setFramerateLimit(FPS);

    // init the game
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->init();

    // start the main loop
    game->loop(window);

    return 0;
}