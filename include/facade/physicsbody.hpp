#pragma once

#include "utils/vec2.hpp"

class b2Body;

namespace Facade {

struct PhysicsBody {
    PhysicsBody() = default;
    explicit PhysicsBody(b2Body*);

    void setVelocity (Vec2f) noexcept;
    void setVelocityX(float) noexcept;
    void setVelocityY(float) noexcept;
    void setPosition (Vec2f) noexcept;

    Vec2f velocity() const noexcept;
    Vec2f position() const noexcept;

    explicit operator bool() const noexcept;
    b2Body* body()           const noexcept;

private:
    b2Body* m_body = nullptr;
};

}
