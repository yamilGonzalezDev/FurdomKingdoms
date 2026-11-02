#include "core/fade.hpp"

Fade::Fade()
    : state{FadeState::FADINGIN}, alpha{255.f} {
        setState(state);
}
void
Fade::update(float dt) {
    (this->*currentState)(dt);
    fadeRect.setSize(m_window->defaultView().getSize());
    fadeRect.setPosition(0.f, 0.f);
    fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));
}
void
Fade::start() {
    setState(FadeState::FADINGOUT);
}
void
Fade::end() {
    setState(FadeState::FADINGIN);
}
bool
Fade::fadedOut() const { return state == FadeState::BLACK; }
void
Fade::render() {
    sf::View old = m_window->getView();
    m_window->setView(m_window->defaultView());
    m_window->draw(fadeRect);
    m_window->setView(old);
}
void
Fade::fadeOut(float dt) {
    alpha += speed * dt;
    if (alpha > 255) {
        alpha = 255;
        setState(FadeState::BLACK);
    }
}
void
Fade::fadeIn(float dt) {
    alpha -= speed * dt;
    if (alpha < 0) {
        alpha = 0;
        setState(FadeState::IDLE);
    }
}
void
Fade::idle (float) {  }
void
Fade::black(float) {  }
void
Fade::setState(FadeState newState) {
    state        = newState;
    currentState = states.at(newState);
}
