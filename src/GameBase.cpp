#include "Game.hpp"

// #define DRAWCOLLIDER

// Structors
Game::Game(){}

Game::~Game(){}

// Methods

// Game init
void Game::init(){
    // init self pointer
    gamePtr = shared_from_this();

    // init all the controls
    initControls();

    // load very first level - menu
    loadLevel("no");

    // init view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);
}

// Main loop
void Game::loop(sf::RenderWindow& window){
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;
    float timeMs;
    while (window.isOpen())
    {
        // Time
        sf::Time deltaTime = clock.restart();
        timeMs = deltaTime.asMicroseconds()/1000.f;
        // Limit max dt
        if(timeMs > 50){
            timeMs = 50;
        }
        // std::cout << 1000.0/timeMs << "FPS ; " << timeMs << "\n";

        // Events
        ControlsManager* controls = ControlsManager::getInstance();
        controls->clearOncePressed();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvent(event);
        }

        // Updates
        window.clear();
        update(window, timeMs);
        window.display();
    }
}

// handle window events
void Game::handleEvent(const sf::Event& event){
    ControlsManager* controls = ControlsManager::getInstance();
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        controls->addOncePressedKeyboard(event.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        controls->addOncePressedMouse(event.mouseButton.button);
        break;
    default:
        break;
    }
}