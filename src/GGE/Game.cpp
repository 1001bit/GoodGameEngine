#include "GGE/Game.hpp"

// #define SHOW_FPS
#define SHOW_FPS_SPIKES

// Structors
Game::Game(){}

Game::~Game(){}

// Methods

// Game init
void Game::init(){
    // Level
    currentLevel = std::make_shared<Level>();
    currentLevel->init();
}

// Main loop
void Game::loop(sf::RenderWindow& window){
    window.setKeyRepeatEnabled(false);

    sf::Clock clock;
    float dTimeMs;
    while (window.isOpen())
    {
        // Time
        sf::Time deltaTime = clock.restart();
        dTimeMs = deltaTime.asMicroseconds()/1000.f;
        // Limit max dt
        if(dTimeMs > 1000/MIN_FPS){
            #ifdef SHOW_FPS_SPIKES
            std::cout << dTimeMs << "\n";
            #endif
            dTimeMs = 1000/MIN_FPS;
        }
        #ifdef SHOW_FPS
        std::cout << "dTime (ms): " << dTimeMs << " ; \t\t" << " FPS: " << 1000/dTimeMs << "\n";
        #endif

        // Events
        ControlsManager* controlsManager = ControlsManager::getInstance();
        controlsManager->clearPressed();

        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvent(event);
        }

        // Updates
        // Cooldowns
        CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
        cooldownsManager->updateCooldowns(dTimeMs);

        // GObjects
        currentLevel->update(dTimeMs);

        // Physics
        PhysicsManager* physicsManager = PhysicsManager::getInstance();
        physicsManager->updatePhysics(dTimeMs);

        // Camera
        currentLevel->camera->update(dTimeMs);

        // Draw
        window.clear();
        currentLevel->drawGObjetcs(window);
        window.display();
    }
}

// handle window events
void Game::handleEvent(const sf::Event& event){
    ControlsManager* controlsManager = ControlsManager::getInstance();
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        controlsManager->addPressedKeyboard(event.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        controlsManager->addPressedMouse(event.mouseButton.button);
        break;

    case sf::Event::KeyReleased:
        controlsManager->keyboardControlRelease(event.key.code);
        break;
    case sf::Event::MouseButtonReleased:
        controlsManager->mouseControlRelease(event.mouseButton.button);

    default:
        break;
    }
}