#pragma once

template <typename T>
struct Vec2 {
    using Vec = Vec2<T>;
    T x;
    T y;

    Vec operator*(T scalar) const {
        return { x * scalar, y * scalar };
    }
    Vec operator*(const Vec& rhs) const {
        return { x * rhs.x, y * rhs.y };
    }
    Vec operator/(T scalar) const {
        return { x /scalar, y / scalar };
    }
    Vec operator+(const Vec& rhs) const {
        return { x + rhs.x, y + rhs.y };
    }
    Vec operator-(const Vec& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }
    T dot(const Vec& rhs) const {
        return ((x * rhs.x) + (y * rhs.y));
    }
    T cross(const Vec& rhs) const {
        return ((x*rhs.y) - (y*rhs.x));
    }
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
