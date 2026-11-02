#include "render/texturemanager.hpp"
#include <stdexcept>
#include <utility>

TextureManager::TextureManager() {}
void
TextureManager::add(const std::string& key, const std::string& path) {
    if ( m_textures.find(key) != m_textures.end() ) return;

    sf::Texture texture;

    if (!texture.loadFromFile(path))
        throw std::runtime_error("ERROR: Couldn't load the texture");

    m_textures.emplace(key, std::move(texture));
}
const sf::Texture&
TextureManager::getTexture(const std::string& key) const {
    return m_textures.at(key);
}
sf::Texture&
TextureManager::getTexture(const std::string& key) {
    return m_textures.at(key);
}
