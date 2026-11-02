#include "facade/physicsbody.hpp"
#include "box2d/box2d.h"

namespace Facade {

PhysicsBody::PhysicsBody(b2Body* b = nullptr) : m_body(b) {}
void
PhysicsBody::setVelocity(Vec2f v) noexcept {
    m_body->SetLinearVelocity({ v.x, v.y });
}
void
PhysicsBody::setVelocityX(float vx) noexcept {
    m_body->SetLinearVelocity({ vx, m_body->GetLinearVelocity().y });
}
void
PhysicsBody::setVelocityY(float vy) noexcept {
    m_body->SetLinearVelocity({ m_body->GetLinearVelocity().x, vy });
}
void
PhysicsBody::setPosition (Vec2f pos) noexcept {
    m_body->SetTransform({ pos.x, pos.y }, m_body->GetAngle() );
}
Vec2f
PhysicsBody::velocity() const noexcept {
    const b2Vec2& v = m_body->GetLinearVelocity();
    return { v.x, v.y };
}
Vec2f
PhysicsBody::position() const noexcept {
    const b2Vec2& p = m_body->GetPosition();
    return { p.x, p.y };
}
PhysicsBody::operator
bool() const noexcept {
    return m_body != nullptr;
}
b2Body*
PhysicsBody::body() const noexcept {
    return m_body;
}

}
