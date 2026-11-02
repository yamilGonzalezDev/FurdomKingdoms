#pragma once

#include "box2d/box2d.h"
#include "physics/collidable.hpp"

struct JumpComponent : public Collidable {
    explicit JumpComponent();
    bool getIsOnGround() const noexcept;
    CollidableType const& getCollidableType() const noexcept final;
    static void onBeginCollision(Collidable&, Collidable&);
    static void onEndCollision  (Collidable&, Collidable&);
private:
    int m_floorContacts{};
    CollidableType m_colision_type = CollidableType::JUMPCMP;
};
