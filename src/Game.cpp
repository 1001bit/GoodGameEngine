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

    // init texture storage
    sf::Texture texture;
    texture.loadFromFile("Assets/Original/Textures/dummy.png");
    textureMap["Original/dummy.png"] = texture;
    texture.loadFromFile("Assets/Original/Textures/sword.png");
    textureMap["Original/sword.png"] = texture;
    texture.loadFromFile("Assets/Original/Textures/platform.png");
    textureMap["Original/platform.png"] = texture;

    // init font storage
    sf::Font font;
    font.loadFromFile("Assets/Original/Fonts/font1.ttf");
    fontMap["Original/font1.ttf"] = font;

    // init all the gameObjects
    initGObjects();

    // init view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);
}

void Game::initGObjects(){
    // Game
    // init dummy
    std::shared_ptr<PhysPlayer> dummy = std::make_shared<PhysPlayer>();
    addNewGameObject(dummy, gamePtr, 0);
    dummy->setRectSize(16, 16);
    dummy->setRelativePos(500, 300);
    // it's camera
    camera = std::make_shared<Camera>();
    addNewGameObject(camera, dummy, 0);
    camera->setSize(GAME_WIDTH, GAME_HEIGHT);

    // his sprite
    std::shared_ptr<AnimatedSprite> dummySprite = std::make_shared<AnimatedSprite>();
    addNewGameObject(dummySprite, dummy, 1);
    dummySprite->insertAnimation("idle", Animation(textureMap.at("Original/dummy.png"), 16, 500, 1));
    dummySprite->playAnimation("idle");
    // and his sword
    std::shared_ptr<GSprite> sword = std::make_shared<GSprite>();
    addNewGameObject(sword, dummy, 2);
    sword->setTexture(textureMap.at("Original/sword.png"));
    sword->setRelativePos(-30, 1);

    // Npc
    std::shared_ptr<PhysNpc> npc = std::make_shared<PhysNpc>();
    addNewGameObject(npc, gamePtr, 0);
    npc->setRectSize(16, 16);
    npc->setRelativePos(500, 300);
    // his sprite
    std::shared_ptr<AnimatedSprite> npcSprite = std::make_shared<AnimatedSprite>();
    addNewGameObject(npcSprite, npc, 1);
    npcSprite->insertAnimation("idle", Animation(textureMap.at("Original/dummy.png"), 16, 500, 1));
    npcSprite->playAnimation("idle");

    // a platform
    std::shared_ptr<SolidBody> platform = std::make_shared<SolidBody>();
    addNewGameObject(platform, gamePtr, 0);
    platform->setRectSize(100, 10);
    platform->setRelativePos(100, 800);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite = std::make_shared<GSprite>();
    addNewGameObject(platformSprite, platform, 0);
    platformSprite->setTexture(textureMap.at("Original/platform.png"));

    // 2nd platform
    std::shared_ptr<SolidBody> platform2 = std::make_shared<SolidBody>();
    addNewGameObject(platform2, gamePtr, 0);
    platform2->setRectSize(100, 10);
    platform2->setRelativePos(800, 730);
    // it's sprite
    std::shared_ptr<GSprite> platformSprite2 = std::make_shared<GSprite>();
    addNewGameObject(platformSprite2, platform2, 0);
    platformSprite2->setTexture(textureMap.at("Original/platform.png"));

    /////////////////////
    // Gui
    std::shared_ptr<GText> text1 = std::make_shared<GText>();
    addNewGuiObject(text1, gamePtr, 0);
    text1->text.setFont(fontMap["Original/font1.ttf"]);
    text1->text.setCharacterSize(30);
    text1->text.setString("Hello dummy!");
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

// update the game
void Game::updateGame(sf::RenderWindow& window, const float& timeMs){
    // iterate through whole map
    for(std::pair<const u_char, GObjectSet> GObjectsLayer : GameLayers){
        // iterate through a single layer
        for(std::shared_ptr<GObject> object : GObjectsLayer.second){
            // update an object
            object->update(timeMs);

            // if current layer == body layer: collide
            if(GObjectsLayer.first == LayerType::LBodies && object->getRect() != sf::FloatRect() && object->getType() == TKinematicBody){
                // collide body with other bodies
                for(std::shared_ptr<GObject> Object2 : GObjectsLayer.second){
                    if(Object2 == object || Object2->getRect() == sf::FloatRect()){
                        continue;
                    }
                    object->collide(Object2);
                }

                // draw collider for debug
                #ifdef DRAWCOLLIDER
                sf::RectangleShape visible = sf::RectangleShape();
                visible.setFillColor(sf::Color::Red);
                visible.setSize(sf::Vector2f(object->getCollider().width, object->getCollider().height));
                visible.setPosition(sf::Vector2f(object->getCollider().left, object->getCollider().top));
                window.draw(visible);
                #endif
            }

            #ifndef DRAWCOLLIDER
            // if drawable - draw on a screen
            if(DRAWABLE_GOBJECT_TYPES.count(object->getType())){
                object->drawSelf(window);
            }
            #endif
        }
    }
}

// update gui
void Game::updateGui(sf::RenderWindow& window, const float& timeMs){
    // iterate through whole map
    for(std::pair<const u_char, GObjectSet> GObjectsLayer : GuiLayers){
        for(std::shared_ptr<GObject> object : GObjectsLayer.second){
            if(!DRAWABLE_GOBJECT_TYPES.count(object->getType())){
                continue;
            }

            object->drawSelf(window);
        }
    }
}

// update all
void Game::update(sf::RenderWindow& window, const float& timeMs){
    window.setView(camera->getView());
    updateGame(window, timeMs);
    window.setView(guiView);
    updateGui(window, timeMs);
}

// add new object to the game
void Game::addNewGameObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer = 0){
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
    if(!GameLayers.count(layer)){
        GameLayers[layer] = GObjectSet{};
    }
    GameLayers[layer].insert(newGObject);
}

// add new object to the game
void Game::addNewGuiObject(std::shared_ptr<GObject> newGObject, std::shared_ptr<GObject> newParent, u_char layer = 0){
    newGObject->setParent(newParent);
    // if layer doesn't exist - make it
    if(!GuiLayers.count(layer)){
        GuiLayers[layer] = GObjectSet{};
    }
    GuiLayers[layer].insert(newGObject);
}