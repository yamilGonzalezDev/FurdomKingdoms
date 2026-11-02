#pragma once

#include <cstddef>

enum class PortalID : std::size_t {
    NONE,
    TO_MENU,
    TO_CITY,
    TO_HOUSE,
    TO_FOREST,
    TO_TEST,
    COUNT
};
