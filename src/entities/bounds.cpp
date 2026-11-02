#include "entities/bounds.hpp"

////////////////////////////////////////////////////////////////////////////////
//
// SENSOR
//
Sensor::Sensor() {

}
CollidableType const&
Sensor::getCollidableType() const noexcept {
    return m_colision_type;
}
void
Sensor::onBeginCollision(Collidable& self, Collidable&) {
    as<Sensor>(self).trigger();
}
////////////////////////////////////////////////////////////////////////////////
//
// PORTAL
//
CollidableType const&
Portal::getCollidableType() const noexcept {
    return m_colision_type;
}

void
Portal::onBeginCollision(Collidable& self, Collidable&) {
    //as(self).
}

////////////////////////////////////////////////////////////////////////////////
//
// FLOOR
//
CollidableType const&
Floor::getCollidableType() const noexcept {
    return m_colision_type;
}

////////////////////////////////////////////////////////////////////////////////
//
// WALL
//
CollidableType const&
Wall::getCollidableType() const noexcept {
    return m_colision_type;
}
