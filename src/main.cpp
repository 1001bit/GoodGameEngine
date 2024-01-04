#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->init(sf::VideoMode(1440, 880), "BeGood Effect", sf::Style::Close);
    return 0;
}