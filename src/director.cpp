#include "director.hpp"
#include <iostream>

void debug()
{
    static int debug = 1;
    std::cout << "Debug " << debug << std::endl;
    debug++;
}

Director::Director()
{
    init();
}

void Director::run()
{
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::LostFocus)
            {
//                player->edificio.setVolume(0.f);
//                music.setVolume(0.f);
            }
            else if (event.type == sf::Event::GainedFocus)
            {
//                player->edificio.setVolume(originalVolume);
//                music.setVolume(originalVolume);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        updateScene(deltaTime);

        update(deltaTime);

        if(drawPlayer)
        {
            if(window.hasFocus())
            {
                player->keyboardInput(deltaTime);
            }

            player->updateAnimation(deltaTime);
        }

        if(transitioning)
            transition(deltaTime);

        render();
    }
}

Director::~Director()
{
    //delete npc;
    delete world;
    delete player;
    delete ground;
    delete collisionCheck;
}

void Director::init()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Furdom Kingdoms");
    window.setFramerateLimit(60);
    currentSceneState = SceneState::MainMenu;
    nextScene = SceneState::House;
    drawPlayer = false;
    transitioning = false;
    transitionTime = 0.f;
    window.setFramerateLimit(60);
    currentScene = nullptr;
    view.setSize(window.getSize().x, window.getSize().y);
}

void Director::initMenuScene()
{
    if(world != nullptr) world = nullptr;
    drawPlayer = false;

    currentScene = new MenuScene;

    sf::Texture texture;
    sf::Sprite sprite;

    if(!texture.loadFromFile("Textures/menu/scroll.png"))
    {
        return;
    }

    sprite.setTexture(texture);
    sprite.setScale(5.f, 5.f);
}

void Director::initHouseScene()
{
    currentScene = new HouseScene;

    drawPlayer = true;

    world = new b2World(b2Vec2(0.f, 9.8f));
    collisionCheck = new Collision();
    world->SetContactListener(collisionCheck);

    ground = new Ground;
    ground->createGround(world, 0.f, 528.f, 1366.f, 0.f);

    player = new Player;
    player->createPlayer(world, 150.f, 400.f);
}

/*void sceneCleanUp(std::string sceneName)
{
    ///llamas todo y le haces delete a todos los punteros
    delete currentScene;
    delete world;
    delete ground;
    delete player;
}

void Director::switchDestructor(SceneState lastScene)
{
    switch(lastScene)
    {
        case SceneState::House:
            sceneCleanUp(house);
            break;
    }
}*/

void Director::render()
{
    window.clear();

    currentScene->render(window);

    /*if(drawPlayer)
    {
        window.draw(player->sprite);
    }*/

    window.display();
}

void Director::update(float deltaTime)
{
    if(currentScene->shouldTransition() && currentSceneState != SceneState::House)
    {
        switchScene(SceneState::House);
    }
    else if(currentScene->shouldTransition() && currentSceneState != SceneState::MainMenu)
    {
        switchScene(SceneState::MainMenu);
    }
}

void Director::transition(float deltaTime)
{
    transitionTime += deltaTime;
    float alpha = std::min(transitionTime / maxTransitionTime, 1.f);

    sf::RectangleShape fade(sf::Vector2f(window.getSize()));
    fade.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(255 * (1.f - alpha))));
    window.draw(fade);

    if(alpha >= 1.f)
    {
        currentSceneState = nextScene;
        transitioning = false;
        transitionTime = 0.f;
    }
}

void Director::switchScene(SceneState newScene)
{

}

void Director::updateScene(float deltaTime)
{
    switch(currentSceneState)
    {
        case SceneState::MainMenu:
            transition(deltaTime);
            initMenuScene();
            break;
        case SceneState::House:
            transition(deltaTime);
            initHouseScene();
            world->Step(deltaTime, 8, 3);
            break;
        case SceneState::Pause:
            break;
    }
}
