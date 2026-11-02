#pragma once

enum class CollidableType {
      PLAYER      // 0
    , FLOOR       // 1
    , SENSOR      // 2
    , WALL        // 3
    , ENEMY       // 4
    , ENEMYSENSOR // 5
    , JUMPCMP     // 6
    , PORTAL      // 7
    , COUNT       // 8
};

#include "facade/physicsbody.hpp"

struct Collidable {
    virtual CollidableType const& getCollidableType() const noexcept = 0;

    void setBody(b2Body* body) { m_body = Facade::PhysicsBody{body}; }

    Facade::PhysicsBody&       body()       noexcept { return m_body; }
    const Facade::PhysicsBody& body() const noexcept { return m_body; }

    virtual ~Collidable() = default;
protected:
    Facade::PhysicsBody m_body;
};

template <typename T>
T& as(Collidable& c) { return static_cast<T&>(c); }
