#pragma once

#include "render/renderable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/View.hpp"
#include <unordered_map>

struct Fade : public Renderable {
    Fade();
    void update(float dt);
    void start();
    void end();
    bool fadedOut() const;
    void render() final;
private:
    using StateFunc = void(Fade::*)(float);
    enum class FadeState {
        FADINGOUT,
        FADINGIN,
        BLACK,
        IDLE
    };
    std::unordered_map<FadeState, StateFunc> states {
        { FadeState::FADINGIN,  &Fade::fadeIn  },
        { FadeState::FADINGOUT, &Fade::fadeOut },
        { FadeState::BLACK,     &Fade::black   },
        { FadeState::IDLE,      &Fade::idle    }
    };
    void setState(FadeState);
    void fadeOut(float);
    void fadeIn (float);
    void idle   (float);
    void black  (float);
    StateFunc currentState = &Fade::fadeIn;
    sf::RectangleShape fadeRect{};
    sf::View view;
    float speed = 200.f;
    FadeState state;
    float alpha;
};
