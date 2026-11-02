#include "entities/enemy.hpp"
#include <cstddef>

Enemy::Enemy(Facade::PhysicsBody& player)
    : sensors{
        std::make_unique<TestSensor>(*this)
      , std::make_unique<NoSensor>(*this)
      , std::make_unique<NoSensor>(*this)
      }
    , m_player(player)
{  }

void
Enemy::update(float dt) {
    chase(dt);
}
void
Enemy::chase(float dt) {
    auto velocity = 5.f;
    auto playerpos = m_player.position();
    auto algo = playerpos.x - m_body.position().x;
    m_body.setVelocityX(((algo > 0 ? 1.f : -1.f) * velocity));
}
CollidableType const&
Enemy::getCollidableType() const noexcept {
    return m_colision_type;
}
EnemySensor*
Enemy::getSensor(const std::size_t& i) { return sensors[i].get(); }
