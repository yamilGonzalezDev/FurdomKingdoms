#include "scene.hpp"

MenuScene::MenuScene()
{
    init();
}

void MenuScene::init()
{
    if(!backgroundTexture.loadFromFile("Textures/menu/scroll.png"))
    {
        std::cerr << "Error cargando las texturas del menu" << std::endl;
    }

    background.setTexture(backgroundTexture);
    //background.setOrigin(WIDTH / 2.f, HEIGHT / 2.f);
    background.setPosition(0.f, 0.f);
    background.setScale(16.f, 16.f);
}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::render(sf::RenderWindow& window)
{
    system("cls");
    window.draw(background);
}

void MenuScene::cleanup()
{

}

bool MenuScene::shouldTransition()
{
    return false;
}

/***/

void HouseScene::init()
{
    if(!backgroundTexture.loadFromFile("Texture/houseLevel/house.png"))
    {
        std::cerr << "Error cargando las texturas de la casa" << std::endl;
    }

    background.setTexture(backgroundTexture);
}

void HouseScene::update(float deltaTime)
{

}

void HouseScene::render(sf::RenderWindow& window)
{
    window.draw(background);
}

void HouseScene::cleanup()
{

}

bool HouseScene::shouldTransition()
{
    return false;
}
