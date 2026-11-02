#pragma once

struct DrawableTexture {
    sf::Texture texture;
    sf::Sprite  sprite;
    void setTexture() {
        if (!texture.loadFromFile(path))
    }
};
