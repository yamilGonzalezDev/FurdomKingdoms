#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "game.hpp"

int main()
{
    Game game;
    game.gameEvents();

    return 0;
}

//#include <ctime>
//
//void move(sf::Sprite&, float);
//
//void moveEnemy(sf::Sprite&, float);
//
//const float moveSpeed = 20.f;
//
//int main()
//{
//    srand(time(0));
//
//    sf::RenderWindow window;
//
//    window.create(sf::VideoMode(800.f, 600.f), "Ejemplo");
//
//    sf::View view;
//    view.setSize(800.f, 600.f);
//    sf::Clock clock;
//
//    sf::Texture text1, text2;
//    sf::Sprite sprite1, sprite2;
//
//    if(!text1.loadFromFile("mcqueen.png"))
//    {
//        std::cerr << "No se pudo cargar el archivo" << std::endl;
//    }
//
//    if(!text2.loadFromFile("fitito.png"))
//    {
//        std::cerr << "No se pudo cargar el archivo" << std::endl;
//    }
//
//    sprite1.setTexture(text1);
//    sprite2.setTexture(text2);
//
//    sprite1.setOrigin(0.f, 0.f);
//    sprite1.setScale(0.2f, 0.2f);
//    sprite1.setPosition(100.f, 100.f);
//
//    sprite2.setOrigin(0.f, 0.f);
//    sprite2.setScale(0.12f, 0.12f);
//    sprite2.setPosition(100.f, 200.f);
//
//    while(window.isOpen())
//    {
//        sf::Event event;
//
//        while(window.pollEvent(event))
//        {
//            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//            {
//                window.close();
//            }
//        }
//
//        float dT = clock.getElapsedTime().asSeconds();
//
//        move(sprite1, dT);
//        moveEnemy(sprite2, dT);
//
//        clock.restart();
//
//        window.clear();
//        window.draw(sprite1);
//        window.draw(sprite2);
//        window.display();
//    }
//
//    return 0;
//}
//
//void move(sf::Sprite& sprite, float deltaTime)
//{
//    sf::Vector2f movement = sf::Vector2f(0.f, 0.f);
//
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//    {
//        movement.x = -moveSpeed;
//    }
//
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        movement.x = moveSpeed;
//    }
//
//    sprite.move(movement * deltaTime);
//
//    movement.x = 0;
//}
//
//void moveEnemy(sf::Sprite& sprite, float deltaTime)
//{
//
//}
