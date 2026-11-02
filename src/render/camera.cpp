#include "render/camera.hpp"
#include "input/keyboard.hpp"
#include "interfaces/cameratarget.hpp"
#include "facade/window.hpp"
#include <iostream>
#include <algorithm>

Camera::Camera(float centerX, float centerY, float sizeX, float sizeY)
    : defaultSize{ sizeX, sizeY } {
    m_view.setCenter(centerX, centerY);
    m_view.setSize(sizeX, sizeY);
}
void
Camera::update(float dt) {
    static float accumulator = 0.f;
    if (!m_canAccumulate)
        accumulator += dt;
    if (accumulator >= 1.f){
        m_canAccumulate = true;
        accumulator = 0.f;
    }
    (this->*modes.at(m_currentMode))(dt);
}
void
Camera::setWindow(Facade::Window* window) {
    m_window = window;
    m_window->setView(m_view);
}
void
Camera::setKeyboard(const FK_Keyboard* keyboard ) {
    m_keyboard_ptr = keyboard;
}
void
Camera::setTarget(CameraTarget* target) {
    m_target      = target;
    m_currentMode = CameraMode::FOLLOW;
}
void
Camera::setFollowPlayer(CameraTarget* target) {
    m_view.setSize(defaultSize.x, defaultSize.y);
    m_window->setView(m_view);
    m_target = target;
    m_currentMode = CameraMode::FOLLOWPLAYER;
}
void
Camera::setMode(CameraMode mode) {
    if ( m_currentMode == mode ) return;
    m_target      = nullptr;
    m_currentMode = mode;
}
void
Camera::zoomIn(float direction = 0.95f) {
    zoom(direction);
}
void
Camera::zoomOut(float direction = 1.05f) {
    zoom(direction);
}
void
Camera::add() {
    if (m_canAccumulate) {
        m_offset.x += 0.f;
        m_offset.y += 1.f;
        m_canAccumulate = false;
    }
}
void
Camera::sub() {
    if (m_canAccumulate) {
        m_offset.x -= 0.f;
        m_offset.y -= 1.f;
        m_canAccumulate = false;
    }
}
void
Camera::setFixedPosition(const Vec2f& pos) {
    elapsed     = 0.f;
    startZoom   = 1.f;
    endZoom     = 2.f;
    duration    = 2.f;
    m_startPos  = { m_view.getCenter().x, m_view.getCenter().y       };
    m_endPos    = { pos.x, pos.y                                     };
    m_startSize = { m_view.getSize().x, m_view.getSize().y           };
    m_endSize   = { m_startSize.x * endZoom, m_startSize.y * endZoom };
}
void
Camera::zoom(float direction) {
    m_view.setSize({ m_view.getSize().x * direction, m_view.getSize().y * direction });
    m_window->setView(m_view);
}
void
Camera::setCenter(float x, float y) {
    m_view = m_window->getView();
    m_view.setCenter(x, y);
    m_window->setView(m_view);
}
void
Camera::move(float x, float y) noexcept {
    m_view = m_window->getView();
    m_view.move(x, y);
    m_window->setView(m_view);
}
void
Camera::freeCamera(float dt) {
    using Key = FK_Keyboard::FK_Key;
    if (!m_keyboard_ptr) return;
    if (m_keyboard_ptr->isKeyPressed(Key::A))
        move(-m_vel * dt, 0.f);
    if (m_keyboard_ptr->isKeyPressed(Key::D))
        move( m_vel * dt, 0.f);
    if (m_keyboard_ptr->isKeyPressed(Key::W))
        move( 0.f, -m_vel * dt);
    if (m_keyboard_ptr->isKeyPressed(Key::S))
        move( 0.f,  m_vel * dt);
}
void
Camera::followCamera(float dt) {
    auto pos = m_target->getPos();
    setCenter((pos.x * m_PPM), (pos.y * m_PPM));
}
void
Camera::followPlayerCamera(float dt) {
    auto pos = m_target->getPos();
    setCenter((pos.x * m_PPM) - m_offset.x, (pos.y * m_PPM) - m_offset.y);
}
void
Camera::fixedCamera(float dt) {
    elapsed += dt;
    float t = std::min(elapsed / duration, 1.f);
    Vec2f pos  = m_startPos  + ( m_endPos  - m_startPos  ) * t;
    Vec2f size = m_startSize + ( m_endSize - m_startSize ) * t;
    m_view.setSize(size.x, size.y);
    m_window->setView(m_view);
    setCenter(pos.x, pos.y);
}
