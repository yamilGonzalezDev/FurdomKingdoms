#pragma once

#include "utils/vec2.hpp"

struct CameraTarget {
    virtual Vec2f getPos() const noexcept = 0;
    virtual ~CameraTarget() = default;
};
