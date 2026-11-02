#pragma once

#include "interfaces/cameratarget.hpp"
#include "physics/collidable.hpp"
#include "render/animator.hpp"
#include "utils/vec2.hpp"

struct Entity : public Collidable, public CameraTarget {
    Vec2f getPos() const noexcept final;
    Animator animator;
};
