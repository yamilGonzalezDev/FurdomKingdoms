#pragma once

#include "scenes/scene.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"

struct MenuScene : public Scene {
    MenuScene(Facade::Window*);
    void render() final;
    void update(float) final;
private:
    bool closeGame();
    void sensorNotify(PortalID) final;
    bool loadFile();
    sf::Texture scrollText;
    sf::Sprite scroll;
    sf::Font font;
    sf::Text menuOptions[4];
    int currentOption = 0;
    bool mainMenu, settingsMenu;
};
