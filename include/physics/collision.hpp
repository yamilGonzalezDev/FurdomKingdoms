#pragma once

#include "box2d/box2d.h"
#include "physics/collisionsTable.hpp"
#include "physics/collidable.hpp"
#include <cstddef>
#include <iostream>

struct Collision : public b2ContactListener {
    explicit Collision();
    ~Collision() = default;
    void BeginContact(b2Contact*) final;
    void EndContact  (b2Contact*) final;
    void PreSolve(b2Contact*, const b2Manifold*) final {}
    void PostSolve(b2Contact*, const b2ContactImpulse*) final {}
private:
    static constexpr std::size_t N = static_cast<std::size_t>(CollidableType::COUNT);
    CollisionTable<N> beginTable{};
    CollisionTable<N> endTable  {};
};

