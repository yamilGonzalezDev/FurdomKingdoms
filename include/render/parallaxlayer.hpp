#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "render/renderable.hpp"
#include "utils/vec2.hpp"
#include <iostream>

struct ParallaxLayer : public Renderable {
    explicit ParallaxLayer() {}
    ~ParallaxLayer() = default;
    void add(sf::Texture& text) {
        text.setRepeated(true);
        m_sprite.setTexture(text);
    }
    void update() {
        if (!m_window) return;
        auto cameraCenter = m_window->getView().getCenter();
        m_sprite.setPosition(m_pos.x + cameraCenter.x * m_factor, m_pos.y);
    }
    void setPosition(const Vec2f& pos) {
        m_pos = pos;
        m_sprite.setPosition(m_pos.x, m_pos.y);
    }
    void render() {
        m_window->draw(m_sprite);
    }
    void setFactor(const float& factor) noexcept { m_factor = factor; }
    void setTextureRect(const sf::IntRect& intRect) noexcept { m_sprite.setTextureRect(intRect); }
    void setScale(const Vec2f& scale) { m_sprite.setScale(scale.x, scale.y); }
    const float& factor()            const noexcept { return m_factor; }
    const sf::Vector2i getTextSize() const noexcept { return static_cast<sf::Vector2i>(m_sprite.getTexture()->getSize()); }
    void move(float x, float y) noexcept { m_pos.x += x; m_pos.y += y; }
private:
    sf::Sprite  m_sprite{};
    Vec2f       m_pos{};
    float       m_factor{};
};
