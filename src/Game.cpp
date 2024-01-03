#include "Game.hpp"

constexpr unsigned FPS = 60;

using std::cout;

// Structors

Game::Game(){
    this->type = gGame;
}

Game::~Game(){}

// Methods
// Game init
void Game::init(sf::VideoMode mode, const sf::String& title, sf::Uint32 style){
    // init self pointer
    gamePtr = shared_from_this();
    // init window
    sf::RenderWindow window(mode, title, style);
    window.setFramerateLimit(FPS);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // init dummy
    std::shared_ptr<PhysBody> dummy = std::make_shared<PhysBody>();
    createNewGObject(dummy, gamePtr, 0);
    dummy->setRelativePos(500, 0);
    // it's camera
    camera = std::make_shared<Camera>();
    createNewGObject(camera, dummy, 0);
    camera->setSize(1440, 880);

    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    createNewGObject(dummySprite, dummy, 0);
    dummySprite->insertAnimation("idle", Animation("Assets/Original/Textures/dummy.png", 16, 500, 1));
    dummySprite->playAnimation("idle");
    // and his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    createNewGObject(sword, dummy, 3);
    sword->setTexture("Assets/Original/Textures/sword.png");
    sword->setRelativePos(-30, 1);
    /////////////////////////////////////////////////////////////////////////////////////////////////

    loop(window);
}

// add new object to the game
void Game::createNewGObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer = 0){
    // first three layers are for non-drawable GObjects
    if(drawableGObjectTypes.count(newGObject->getType())){
        layer += 3;
    } else {
        switch (newGObject->getType())
        {
        case gCollider:
            layer = layerType::colliders;
            break;
        case gCamera:
            layer = layerType::camera;
            break;
        default:
            layer = layerType::invisibles;
            break;
        }
    }

    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GObjectsLayers.count(layer)){
        GObjectsLayers[layer] = GObjectSet{};
    }
    GObjectsLayers[layer].insert(newGObject);
}

// Main loop
void Game::loop(sf::RenderWindow& window){
    sf::Clock clock;
    float timeMs;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeMs = deltaTime.asMicroseconds()/1000.f;
        cout << 1000.0/timeMs << "FPS ; " << timeMs << "\n";

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        update(window, timeMs);
        window.display();
    }
}

// update and draw
void Game::update(sf::RenderWindow& window, const float& timeMs){
    window.setView(camera->getView());
    // iterate through whole map
    for(std::pair<const u_char, GObjectSet > GObjects : GObjectsLayers){
        // iterate through a single layer
        for(std::shared_ptr<GObject> Object : GObjects.second){
            // update an object
            Object->update(timeMs);
            // draw it
            if(drawableGObjectTypes.count(Object->getType())){
                window.draw(Object->getSprite());
            }
        }
    }
}