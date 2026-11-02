#pragma once

#include <cstddef>

namespace sf { class Sprite; }
struct Animation;

struct Animator {
    explicit Animator() noexcept = default;

    void setSprite(sf::Sprite&) noexcept;

    void play  (const Animation&) noexcept;
    void update(float)            noexcept;
    void flipX (bool)             noexcept;

private:
    sf::Sprite*      m_sprite  = nullptr;
    const Animation* m_current = nullptr;
    std::size_t      m_frame   = 0;
    float            m_elapsed = 0.f;
};
