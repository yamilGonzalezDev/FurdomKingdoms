#include "physics/physicsfactory.hpp"
#include "box2d/box2d.h"
#include "entities/enemy.hpp"
#include "physics/collidable.hpp"
#include "entities/player.hpp"
#include "entities/bounds.hpp"
#include <iostream>
#include <cstdint>

PhysicsFactory::PhysicsFactory(b2World& world)
    : m_world(world) {}
b2Body*
PhysicsFactory::createPlayer(const Vec2f& dimensions, Collidable* object) {
    b2Body* body = createDynamicBody();
    auto& fix = setFixture(*body, dimensions, object);
    fix.SetDensity (1.f);
    fix.SetFriction(0.f);
    body->SetFixedRotation(true);
    auto& sensorfix = addSensorFixture(*body, {0.25f, 0.1f}, {0.f, 0.55f});
    auto* pla = static_cast<Player*>(object);
    sensorfix.GetUserData().pointer = reinterpret_cast<uintptr_t>(static_cast<Collidable*>(&pla->jumpcmp));
    body->ResetMassData();

    return body;
}
b2Body*
PhysicsFactory::createEnemy (const Vec2f& dimensions, Enemy&      object) {
    b2Body* body = createDynamicBody();
    auto& mainFix = setFixture(*body, dimensions, &object);
    mainFix.SetDensity(1.f);
    mainFix.SetFriction(1.f);
    body->SetFixedRotation(true);
    auto& sensorFix = setFixture(*body, {dimensions.x * 10.f, dimensions.y}, object.getSensor(0));
    sensorFix.SetSensor(true);
    body->ResetMassData();
    return body;
}
b2Body*
PhysicsFactory::createEntity(const Vec2f& dimensions, Collidable* object) {
    b2Body* body = createDynamicBody();
    auto& fix = setFixture(*body, dimensions, object);
    fix.SetDensity(1.f);
    fix.SetFriction(1.f);
    body->SetFixedRotation(true);
    body->ResetMassData();
    return body;
}
b2Body*
PhysicsFactory::createSensor(const Vec2f& dimensions, Collidable* object) {
    auto* body = createStaticBody();
    auto& fix = addSensorFixture(*body, dimensions, {0, 0});
    fix.GetUserData().pointer = reinterpret_cast<uintptr_t>(object);
    body->ResetMassData();
    return body;
}
b2Body*
PhysicsFactory::createStaticBody () {
    return createBody(b2BodyType::b2_staticBody);
}
b2Body*
PhysicsFactory::createDynamicBody() {
    return createBody(b2BodyType::b2_dynamicBody);
}
b2Body*
PhysicsFactory::createBody(b2BodyType type) {
    b2BodyDef bodyDef;
    bodyDef.type = type;
    b2Body* body = m_world.CreateBody(&bodyDef);
    return body;
}
b2Fixture&
PhysicsFactory::setFixture(b2Body& body, const Vec2f& dimensions, Collidable* object) {
    b2PolygonShape box;
    box.SetAsBox(dimensions.x, dimensions.y);
    b2FixtureDef fix;
    fix.shape = &box;
    fix.userData.pointer = reinterpret_cast<uintptr_t>(object);
    return *(body.CreateFixture(&fix));
}
b2Fixture&
PhysicsFactory::addSensorFixture(b2Body& body, const Vec2f& dimensions, const Vec2f& offset) {
    b2PolygonShape box;
    box.SetAsBox(dimensions.x, dimensions.y, b2Vec2(offset.x, offset.y), 0.f);
    b2FixtureDef fix;
    fix.shape = &box;
    fix.isSensor = true;
    return *(body.CreateFixture(&fix));
}
