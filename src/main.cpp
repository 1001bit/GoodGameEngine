#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440, 880), "BeGood Effect", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Clock clock;
    float timeMs;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeMs = deltaTime.asMicroseconds()/1000.0;
        cout << 1000.0/timeMs << "FPS ; " << timeMs << "\n";
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.display();
    }

    return 0;
}