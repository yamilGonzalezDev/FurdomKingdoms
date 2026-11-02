#include "render/spritemanager.hpp"
#include "facade/physicsbody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <cassert>

void
SpriteManager::update() {
    assert(m_body && *m_body && "SpriteManager without body");
    m_currPos = m_body->position();
}
void
SpriteManager::render() {
    assert(m_spr && "SpriteManager without sprite");
    m_spr->setPosition( m_currPos.x * 30.f, m_currPos.y * 30.f );
}
void
SpriteManager::set(sf::Sprite& spr, const Facade::PhysicsBody& body) {
    m_spr  = &spr;
    m_body = &body;
    m_spr->setOrigin(m_spr->getLocalBounds().width / 2, m_spr->getLocalBounds().height / 2);
}
