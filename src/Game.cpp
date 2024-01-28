#include "Game.hpp"

// Structors
Game::Game(){}

Game::~Game(){}

// Methods

// Game init
void Game::init(){
    // Main game inits
    // controls
    initControls();

    // Level
    currentLevel = std::make_shared<Level>();
    currentLevel->init();
    currentLevel->initTestGObjects();
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
            // std::cout << dTimeMs << "\n";
            dTimeMs = 1000/MIN_FPS;
        }
        // std::cout << "dTime (ms): " << dTimeMs << " ; \t\t" << " FPS: " << 1000/dTimeMs << "\n";

        // Events
        ControlsManager* controlsManager = ControlsManager::getInstance();
        controlsManager->clearOncePressed();

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

// init necessary controls
void Game::initControls(){
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

// handle window events
void Game::handleEvent(const sf::Event& event){
    ControlsManager* controlsManager = ControlsManager::getInstance();
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        controlsManager->addOncePressedKeyboard(event.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        controlsManager->addOncePressedMouse(event.mouseButton.button);
        break;
    default:
        break;
    }
}