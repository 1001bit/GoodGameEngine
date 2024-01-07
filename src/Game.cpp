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

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // init dummy
    std::shared_ptr<TDPlayer> dummy = std::make_shared<TDPlayer>();
    createNewGObject(dummy, gamePtr, 0);
    dummy->setRectSize(16, 16);
    dummy->setRelativePos(500, 300);
    // it's camera
    camera = std::make_shared<Camera>();
    createNewGObject(camera, dummy, 0);
    camera->setSize(1440, 880);

    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    createNewGObject(dummySprite, dummy, 1);
    dummySprite->insertAnimation("idle", Animation("Assets/Original/Textures/dummy.png", 16, 500, 1));
    dummySprite->playAnimation("idle");
    // and his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    createNewGObject(sword, dummy, 2);
    sword->setTexture("Assets/Original/Textures/sword.png");
    sword->setRelativePos(-30, 1);

    // a platform
    std::shared_ptr<SolidBody> platform = std::make_shared<SolidBody>();
    createNewGObject(platform, gamePtr, 0);
    platform->setRectSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    createNewGObject(platformSprite, platform, 0);
    platformSprite->setTexture("Assets/Original/Textures/platform.png");

    // 2nd platform
    std::shared_ptr<SolidBody> platform2 = std::make_shared<SolidBody>();
    createNewGObject(platform2, gamePtr, 0);
    platform2->setRectSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    createNewGObject(platformSprite2, platform2, 0);
    platformSprite2->setTexture("Assets/Original/Textures/platform.png");
}

// Main loop
void Game::loop(sf::RenderWindow& window){
    sf::Clock clock;
    float timeMs;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeMs = deltaTime.asMicroseconds()/1000.f;
        // Limit max dt
        if(timeMs > 50){
            timeMs = 50;
        }
        std::cout << 1000.0/timeMs << "FPS ; " << timeMs << "\n";

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
    for(std::pair<const u_char, GObjectSet> GObjectsLayer : GObjectsLayers){
        // iterate through a single layer
        for(std::shared_ptr<GObject> Object : GObjectsLayer.second){
            // update an object
            Object->update(timeMs);

            // if current layer == body layer: collide
            if(GObjectsLayer.first == LayerType::LBodies && Object->getRect() != sf::FloatRect() && Object->getType() == TKinematicBody){
                // collide body with other bodies
                for(std::shared_ptr<GObject> Object2 : GObjectsLayer.second){
                    if(Object2 == Object || Object2->getRect() == sf::FloatRect()){
                        continue;
                    }
                    Object->collide(Object2);
                }

                // draw collider for debug
                #ifdef DRAWCOLLIDER
                sf::RectangleShape visible = sf::RectangleShape();
                visible.setFillColor(sf::Color::Red);
                visible.setSize(sf::Vector2f(Object->getCollider().width, Object->getCollider().height));
                visible.setPosition(sf::Vector2f(Object->getCollider().left, Object->getCollider().top));
                window.draw(visible);
                #endif
            }

            #ifndef DRAWCOLLIDER
            // if drawable - draw on a screen
            if(DRAWABLE_GOBJECT_TYPES.count(Object->getType())){
                window.draw(Object->getSprite());
            }
            #endif
        }
    }
}

// add new object to the game
void Game::createNewGObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer = 0){
    // first three layers are for non-drawable GObjects
    if(DRAWABLE_GOBJECT_TYPES.count(newGObject->getType())){
        layer += 3;
    } 
    // very first layer is for bodies
    else if (BODY_GOBJECT_TYPES.count(newGObject->getType())) {
        layer = LayerType::LBodies;
    } 
    // third layer is for camera only
    else if (newGObject->getType() == TCamera){
        layer = LayerType::LCamera;
    } 
    // second layer is for all other types
    else {
        layer = LayerType::LInvisibles;
    }

    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GObjectsLayers.count(layer)){
        GObjectsLayers[layer] = GObjectSet{};
    }
    GObjectsLayers[layer].insert(newGObject);
}