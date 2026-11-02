#include "components/jumpcomponent.hpp"

JumpComponent::JumpComponent() {}
bool
JumpComponent::getIsOnGround() const noexcept { return (m_floorContacts > 0); }
void
JumpComponent::onBeginCollision(Collidable& self, Collidable&) {
    as<JumpComponent>(self).m_floorContacts++;
}
void
JumpComponent::onEndCollision(Collidable& self, Collidable&) {
    as<JumpComponent>(self).m_floorContacts--;
}
CollidableType const&
JumpComponent::getCollidableType() const noexcept {
    return m_colision_type;
}
