#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  Collision map
//
//  Begin:
//      JumpComponent -> Floor
//      Sensor        -> Player
//      EnemySensor   -> Player
//  End:
//      JumpComponent -> Floor
//
#include "physics/collidable.hpp"
#include <cstddef>
#include <array>

template <std::size_t Size>
class CollisionTable {
    using SolvingFunc = void(*)(Collidable&, Collidable&);

    template <SolvingFunc F>
    static void pair(Collidable& a, Collidable& b) { F(b, a); }

    static constexpr std::size_t id(CollidableType t) { return static_cast<std::size_t>(t); }
    std::array<std::array<SolvingFunc, Size>, Size> handlers {};
public:
    explicit CollisionTable() {}
    void solve(Collidable& a, Collidable& b) const {
        auto typeA = id(a.getCollidableType());
        auto typeB = id(b.getCollidableType());
        if (!handlers[typeA][typeB]) return;
        handlers[typeA][typeB](a, b);
    }
    template < SolvingFunc handler >
    void addMirror( CollidableType a, CollidableType b) {
        handlers[id(a)][id(b)] = handler;
        handlers[id(b)][id(a)] = &pair<handler>;
    }
    template < SolvingFunc handler >
    void add( CollidableType a, CollidableType b ) {
        handlers[id(a)][id(b)] = handler;
    }
};
