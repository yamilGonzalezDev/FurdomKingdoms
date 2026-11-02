#pragma once

#include "physics/collidable.hpp"

struct Enemy;

struct EnemySensor : public Collidable {
    explicit EnemySensor(Enemy& e) : m_enemy(e) {}
    virtual ~EnemySensor() = default;
protected:
    Enemy& m_enemy;
};

struct NoSensor : public EnemySensor {
    NoSensor(Enemy& e) : EnemySensor(e) {}
    CollidableType const& getCollidableType() const noexcept{
        return m_colision_type;
    }
private:
    CollidableType m_colision_type = CollidableType::ENEMY;
};

struct TestSensor : public EnemySensor {
    TestSensor(Enemy& e) : EnemySensor(e) {}
    CollidableType const& getCollidableType() const noexcept{
        return m_colision_type;
    }
private:
    CollidableType m_colision_type = CollidableType::ENEMY;
};
