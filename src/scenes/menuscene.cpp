#include "scenes/menuscene.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/Color.hpp"
#include <iostream>
#include <cassert>

/**MENU**/
MenuScene::MenuScene(Facade::Window* window_ptr) {
    m_window = window_ptr;
    if( !scrollText.loadFromFile("Textures/menu/scroll.png") ) {
        std::cerr << "Failed to load menu texture: Textures/menu/scroll.png\n";
        return;
    }

    if ( !font.loadFromFile("Textures/font/menuFont.ttf") ) {
        std::cerr << "Failed to load menu font: Textures/font/menuFont.ttf\n";
        return;
    }

    for ( int i = 0; i < 4; i++ ) {
        menuOptions[i].setFont(font);
        menuOptions[i].setCharacterSize(50);
        menuOptions[i].setOutlineThickness(2.f);
    }

    float totalHeight = menuOptions[0].getGlobalBounds().height + 70.f;

    menuOptions[0].setString("Start");
    menuOptions[0].setOrigin(menuOptions[0].getGlobalBounds().width / 2, menuOptions[0].getGlobalBounds().height / 2);
    menuOptions[0].setPosition(WIDTH / 2, HEIGHT / 2 - totalHeight * 2);
    menuOptions[0].setFillColor(sf::Color::Yellow);

    menuOptions[1].setString("Load Game");
    menuOptions[1].setOrigin(menuOptions[1].getGlobalBounds().width / 2, menuOptions[1].getGlobalBounds().height / 2);
    menuOptions[1].setPosition(WIDTH / 2, HEIGHT / 2 - totalHeight * 2 + 70.f);
    menuOptions[1].setFillColor(sf::Color::White);

    menuOptions[2].setString("Settings");
    menuOptions[2].setOrigin(menuOptions[2].getGlobalBounds().width / 2, menuOptions[2].getGlobalBounds().height / 2);
    menuOptions[2].setPosition(WIDTH / 2, HEIGHT / 2 + 5.f);
    menuOptions[2].setFillColor(sf::Color::White);

    menuOptions[3].setString("Exit");
    menuOptions[3].setOrigin(menuOptions[3].getGlobalBounds().width / 2, menuOptions[3].getGlobalBounds().height / 2);
    menuOptions[3].setPosition(WIDTH / 2, HEIGHT / 2 + totalHeight);
    menuOptions[3].setFillColor(sf::Color::White);

    scroll.setTexture(scrollText);
    scroll.setScale(13.f, 13.f);
    scroll.setOrigin(scroll.getLocalBounds().width / 2, scroll.getLocalBounds().height / 2);
    scroll.setPosition(WIDTH / 2, HEIGHT / 2);
}

void
MenuScene::update(float deltaTime) {
    const float cooldown = 0.4f;
    static float currentCooldown = 0.f;

    currentCooldown -= deltaTime;

    if((    sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    ||      sf::Keyboard::isKeyPressed(sf::Keyboard::W ))
    &&      currentCooldown <= 0.f) {
        if (currentOption > 0) currentOption--;
        else currentOption = 3;
        currentCooldown = cooldown;
    }
    else if((    sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
    ||           sf::Keyboard::isKeyPressed(sf::Keyboard::S   ))
    &&           currentCooldown <= 0.f) {
        if (currentOption < 3) currentOption++;
        else currentOption = 0;
        currentCooldown = cooldown;
    }

    for ( int i = 0; i < 4; i++ ) {
        if ( i == currentOption ) menuOptions[i].setFillColor(sf::Color::Yellow);
        else menuOptions[i].setFillColor(sf::Color::White);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
    &&   currentOption == 0) {
        sensorTrigger(PortalID::TO_HOUSE);
    }
}

void
MenuScene::render() {
    assert(m_window);
    m_window->draw( scroll         );
    m_window->draw( menuOptions[0] );
    m_window->draw( menuOptions[1] );
    m_window->draw( menuOptions[2] );
    m_window->draw( menuOptions[3] );
}

void
MenuScene::sensorNotify(PortalID n_p_id) {
    if ( currentOption == 0
    &&   sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        sensorTrigger(PortalID::TO_HOUSE);
    }
}

bool
MenuScene::loadFile() {
    return false;
}

bool
MenuScene::closeGame() {
    return (currentOption == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
}
