#include "game.hpp"

void mensaje()
{
    std::cout << "Hasta acá llego" << std::endl;
}

Ground::Ground() : PPM(30.f) {};

Game::Game()
    : gravity(0.f, 15.f), collisionCheck(new Collision())
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Furdom Kingdoms");
    //director = new Director();
    window.setFramerateLimit(60);
    view.setSize(WIDTH, HEIGHT);
    world = new b2World(gravity);
    ground = new Ground;

    world->SetContactListener(collisionCheck);
    ground->createGround(world, 0.f, FLOORHEIGHT, WIDTH, 0.f);
    player = new Player;
    player->createPlayer(world, 150.f, 400.f);

    createWall(13.f, FLOORHEIGHT - 112.f, 16.f, 112.f);
    createWall(748.f, FLOORHEIGHT - 112.f, 16.f, 112.f);

    npc = new Npc(world, 400.f, 400.f);
}

void Game::gameEvents()
{
    Enemy enemy;

    sf::Texture house;
    sf::Sprite houseSprite;

    if(!house.loadFromFile("Textures/menu/scroll.png"))
    {
        return;
    }

    houseSprite.setTexture(house);

//    int bodyCount = 0;
//    for(b2Body* b = world->GetBodyList(); b != nullptr; b = b->GetNext())
//    {
//        bodyCount++;
//    }
//
//    std::cout << "Cantidad de cuerpos en el mundo: " << bodyCount << std::endl;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                music.stop();
                window.close();
            }
            if (event.type == sf::Event::LostFocus)
            {
                player->edificio.setVolume(0.f);
                music.setVolume(0.f);
            }
            else if (event.type == sf::Event::GainedFocus)
            {
                player->edificio.setVolume(originalVolume);
                music.setVolume(originalVolume);
            }
        }

        float deltaTime = clock.getElapsedTime().asSeconds();

        world->Step(timeStep, velocityIterations, positionIterations);

        if(window.hasFocus())
        {
            player->keyboardInput(deltaTime);
        }

        player->updateAnimation(deltaTime);

        /*npc->npcMove(deltaTime);
        npc->updateAnimation(deltaTime);*/

        enemy.enemyAnimation(deltaTime);

        //view.setCenter(player->playerHitbox->getPosition().x + 33.f, player->playerHitbox->getPosition().y + 48.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            std::cout << std::endl << "Esta en el piso? ";
            if(player->getIsOnGround()) std::cout << "si";
            else { std::cout << "no"; }
        }

        clock.restart();
        window.clear();
        //window.setView(view);
        window.draw(houseSprite);
        window.draw(player->sprite);
        //window.draw(*player->playerHitbox);
        /*window.draw(npc->sprite);
        window.draw(npc->npcHitBox);*/
        enemy.popUps(window, deltaTime);
        //window.draw(*groundShape);
        //window.draw(*wallShape);
        window.display();
    }
}



void Game::createWall(float x, float y, float width, float height)
{
    b2BodyDef wallBodyDef;
    wallBodyDef.type = b2_staticBody;
    wallBodyDef.position.Set(x / pixels_per_meter, y / pixels_per_meter);

    b2Body* wallBody = world->CreateBody(&wallBodyDef);

    b2PolygonShape wallBox;
    wallBox.SetAsBox(width / pixels_per_meter, height / pixels_per_meter);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wallBox;
    fixtureDef.density = 0.f;
    fixtureDef.friction = 0.4f;

    wallBody->CreateFixture(&fixtureDef);

    wallShape = new sf::RectangleShape(sf::Vector2f(width, height));
    wallShape->setPosition((wallBody->GetPosition().x * pixels_per_meter) + 54, wallBody->GetPosition().y * pixels_per_meter);
    wallShape->setOutlineColor(sf::Color::White);
    wallShape->setOutlineThickness(0.5f);
    //groundShape->setFillColor(sf::Color::Transparent);

    wallBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(wallShape);
}

Game::~Game()
{
    delete collisionCheck;

    delete world;
}

void Game::destroyBody(b2Body* body)
{
    world->DestroyBody(body);
}
