#pragma once

#include "entities/entity.hpp"
#include "physics/collidable.hpp"
#include "components/enemysensor.hpp"
#include <array>
#include <cstddef>
#include <memory>

namespace Facade { struct PhysicsBody; }

struct Enemy : public Entity {
    Enemy(Facade::PhysicsBody&);
    void update(float);
    void chase(float);
    CollidableType const& getCollidableType() const noexcept final;
    EnemySensor* getSensor(const std::size_t&);
private:
    std::array<std::unique_ptr<EnemySensor>, 3> sensors;
    Facade::PhysicsBody& m_player;
    CollidableType m_colision_type = CollidableType::ENEMY;
};
