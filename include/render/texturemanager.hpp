#pragma once

#include <unordered_map>
#include <string>
#include "SFML/Graphics/Texture.hpp"


struct TextureManager {
    TextureManager();
    void add(const std::string&, const std::string&);
    const sf::Texture& getTexture(const std::string&) const;
    sf::Texture& getTexture(const std::string&);
private:
    std::unordered_map<std::string, sf::Texture> m_textures {};
};
