#pragma once

#include "utils/vec2.hpp"
#include "box2d/box2d.h"

struct Collidable;
struct Enemy;

struct PhysicsFactory {
    using body_ptr = b2Body*;
    explicit PhysicsFactory(b2World& world);
    ~PhysicsFactory() = default;
    body_ptr createEnemy (const Vec2f&, Enemy&     );
    body_ptr createPlayer(const Vec2f&, Collidable*);
    body_ptr createEntity(const Vec2f&, Collidable*);
    body_ptr createSensor(const Vec2f&, Collidable*);
    template <typename T>
    body_ptr createBound(const Vec2f& halfSize, Collidable* object) {
        b2Body* body = createStaticBody();
        auto& fix = setFixture(*body, halfSize, object);
        fix.SetFriction(T::friction);
        body->ResetMassData();
        return body;
    }
private:
    body_ptr createStaticBody();
    body_ptr createDynamicBody();
    body_ptr createBody(b2BodyType);
    b2Fixture& setFixture(b2Body&, const Vec2f&, Collidable*);
    b2Fixture& addSensorFixture(b2Body&, const Vec2f&, const Vec2f&);

    b2World& m_world;
};
