#include "entities/entity.hpp"

Vec2f
Entity::getPos() const noexcept {
    return m_body.position();
}
