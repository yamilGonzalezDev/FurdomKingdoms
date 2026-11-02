#include "physics/physicsworld.hpp"
#include "physics/physicsfactory.hpp"
#include "events/sensorobserver.hpp"
#include "physics/physicsworld.hpp"
#include "physics/collidable.hpp"
#include "physics/collision.hpp"
#include "entities/bounds.hpp"
#include "physics/fooDraw.hpp"
#include "entities/player.hpp"
#include "box2d/box2d.h"
#include <iostream>

PhysicsWorld::PhysicsWorld()
    : m_world    ( std::make_unique<b2World>       (b2Vec2(0.f, 9.8f)) )
    , m_factory  ( std::make_unique<PhysicsFactory>(*m_world         ) )
    , m_collision( std::make_unique<Collision>     (                 ) )
    , m_fooDraw  ( std::make_unique<FooDraw>       (                 ) ) {
    m_fooDraw->SetFlags(b2Draw::e_shapeBit);
    m_world->SetDebugDraw(m_fooDraw.get());
    m_world->SetContactListener(m_collision.get());
    m_data.reserve(100);
}
PhysicsWorld::~PhysicsWorld() = default;
template <typename BoundType>
void
PhysicsWorld::create(Vec2f halfSize, Vec2f pos) {
    auto& bound = m_data.emplace_back(std::make_unique<BoundType>());
    bound->setBody(m_factory->createBound<BoundType>(halfSize, bound.get()));
    bound->body().setPosition({pos.x, pos.y});
}
b2Body*
PhysicsWorld::createMovableBody(Vec2f halfSize, Vec2f pos) {
    auto& bound = m_data.emplace_back(std::make_unique<Floor>());
    bound->setBody(m_factory->createBound<Floor>(halfSize, bound.get()));
    bound->body().setPosition(pos);
    return bound->body().body();
}
void
PhysicsWorld::createPlayer(Vec2f halfSize, Vec2f pos, Player* player) {
    player->setBody(m_factory->createPlayer(halfSize, player));
    player->body().setPosition({pos.x, pos.y});
}
void
PhysicsWorld::createFloor(Vec2f halfSize, Vec2f pos) {
    create<Floor>(halfSize, pos);
}
void
PhysicsWorld::createWall(Vec2f halfSize, Vec2f pos) {
    create<Wall>(halfSize, pos);
}
void
PhysicsWorld::createSensor(Vec2f halfSize, Vec2f pos, SensorObserver& other) {
    auto& sensor = m_data.emplace_back(std::make_unique<Sensor>());
    as<Sensor>(*sensor).addObserver(&other);
    sensor->setBody(m_factory->createSensor(halfSize, sensor.get()));
    sensor->body().setPosition({pos.x, pos.y});
}
void
PhysicsWorld::step(float dt) {
    m_accumulator += dt;
    while ( m_accumulator >= m_timeStep ) {
        m_world->Step(m_timeStep, m_velIter, m_posIter);
        m_accumulator -= m_timeStep;
    }

}
void
PhysicsWorld::render() {
    m_world->DebugDraw();
}
void
PhysicsWorld::setWindow(Facade::Window* window) {
    m_fooDraw->setWindow(window);
}
