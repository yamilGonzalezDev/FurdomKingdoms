#pragma once

#include "events/sceneobserver.hpp"
#include "events/sensorobserver.hpp"
#include "scenes/portalid.hpp"
#include "entities/entity.hpp"

struct Sensor : public Entity, public SensorSubject {
    explicit Sensor();
    static constexpr float friction = 0.f;
    CollidableType const& getCollidableType() const noexcept final;
    static void onBeginCollision(Collidable&, Collidable&);
private:
    static constexpr CollidableType m_colision_type = CollidableType::SENSOR;
};

struct Portal : public Entity, public SceneSubject {
    CollidableType const& getCollidableType() const noexcept final;
    static void onBeginCollision(Collidable&, Collidable&);
private:
    static constexpr CollidableType m_colision_type = CollidableType::PORTAL;
    PortalID p_id = PortalID::NONE;
};

struct Floor : public Entity {
    static constexpr float friction = 1.f;
    CollidableType const& getCollidableType() const noexcept final;
private:
    static constexpr CollidableType m_colision_type = CollidableType::FLOOR;
};

struct Wall : public Entity {
    static constexpr float friction = 0.f;
    CollidableType const& getCollidableType() const noexcept final;
private:
    static constexpr CollidableType m_colision_type = CollidableType::WALL;
};
