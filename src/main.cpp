#include <iostream>
#include <SFML/Graphics.hpp>

constexpr float viewLerp = 0.015;

using std::cout;

void smoothViewMovement(sf::View& view, sf::Vector2f followPosition, float time){
    sf::Vector2f viewPos = view.getCenter();
    viewPos += (followPosition - viewPos) * time * viewLerp;
    view.setCenter(viewPos);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440, 880), "Such a Happy Face", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Clock clock;
    float timeMs;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeMs = deltaTime.asMicroseconds()/1000.0;
        cout << int(1000.0/timeMs) << "FPS ; " << timeMs << "\n";
        
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