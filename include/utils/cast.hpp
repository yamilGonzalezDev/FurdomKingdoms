#pragma once

#include <cstddef>

template <typename T>
[[nodiscard]] constexpr std::size_t to_size_t(T value) noexcept {
    return static_cast<std::size_t>(value);
}
