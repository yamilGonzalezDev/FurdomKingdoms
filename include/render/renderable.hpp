#pragma once

#include "facade/window.hpp"

struct Renderable {
    virtual void setWindow(Facade::Window* window) { m_window = window; }
    virtual ~Renderable() = default;
    virtual void render() = 0;
protected:
    Facade::Window* m_window = nullptr;
};
