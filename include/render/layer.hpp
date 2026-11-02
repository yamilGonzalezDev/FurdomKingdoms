#pragma once

#include "render/renderable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <iostream>
#include <array>
#include <cstddef>
#include <cassert>

template <std::size_t Capacity = 20>
struct Layer : public Renderable {
    explicit Layer() {}
    ~Layer() = default;
    sf::Sprite& add(const sf::Texture& texture) {
        assert( m_size < Capacity );
        m_sprites[ m_size ].setTexture( texture );
        ++m_size;
        return m_sprites[m_size - 1];
    }
    [[nodiscard]] std::size_t size() const noexcept {
        return m_size;
    }
    [[nodiscard]] constexpr std::size_t capacity() const noexcept {
        return Capacity;
    }
    void render() {
        for ( std::size_t i{}; i < m_size; ++i )
            m_window->draw(m_sprites[i]);
    }
private:
    std::size_t m_size {};
    std::array<sf::Sprite, Capacity>  m_sprites  {};
};
