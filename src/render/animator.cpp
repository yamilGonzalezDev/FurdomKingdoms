#include "render/animator.hpp"

#include "render/animations.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <cmath>
#include <cassert>

void
Animator::setSprite( sf::Sprite& sprite ) noexcept {
    m_sprite = &sprite;
}

void
Animator::play(const Animation& animation) noexcept {
    assert( !animation.frames.empty() && "Animation doesn't have frames" );
    if (&animation == m_current) return;
    m_current = &animation;
    m_frame   = 0;
    m_elapsed = 0;
    m_sprite->setTextureRect(animation.frames[0] );
}
void
Animator::update(float dt) noexcept {
    assert( m_current && "Animator without animations. Need a play()");
    m_elapsed += dt;
    if (m_elapsed < m_current->frameDuration) return;
    m_elapsed = 0.f;
    m_frame   = (m_frame + 1) % m_current->frames.size();
    m_sprite->setTextureRect(m_current->frames[m_frame]);
}

void
Animator::flipX(bool flip) noexcept {
    assert(m_sprite && "Animator without sprite");
    sf::Vector2f scale = m_sprite->getScale();
    float x = std::abs(scale.x);
    m_sprite->setScale(flip ? -x : x, scale.y);
}
