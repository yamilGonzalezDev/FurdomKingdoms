#pragma once

#include <vector>
#include <utility>
#include "SFML/Graphics/Rect.hpp"

struct Animation {
    std::vector<sf::IntRect> frames;
    float frameDuration{};

    Animation() = default;

    Animation(std::vector<sf::IntRect> frames, float duration)
        : frames(std::move(frames))
        , frameDuration(duration)
    {}
};
