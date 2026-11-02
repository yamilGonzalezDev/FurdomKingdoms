#pragma once

#include "utils/vec2.hpp"

namespace sf     { class Sprite;      }
namespace Facade { class PhysicsBody; }

struct SpriteManager {
    void set(sf::Sprite&, const Facade::PhysicsBody&);
    void update();
    void render();
private:
    sf::Sprite*                m_spr  = nullptr;
    const Facade::PhysicsBody* m_body = nullptr;
    Vec2f                      m_currPos{};
};
