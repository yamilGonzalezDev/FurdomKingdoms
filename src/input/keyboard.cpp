#include "input/keyboard.hpp"

bool
FK_Keyboard::isKeyPressed(FK_Key k) const noexcept {
    return m_keys[k];
}
bool
FK_Keyboard::justPressed(FK_Key k) const noexcept {
    return m_keys[k] && !m_prev[k];
}

void
FK_Keyboard::beginFrame() noexcept {
    m_prev = m_keys;
}
void
FK_Keyboard::releaseAll() noexcept {
    m_keys.fill(false);
}

void
FK_Keyboard::press  (FK_Key k) noexcept {
    if ( k != FK_Key::Unknown ) m_keys[k] = true;
}
void
FK_Keyboard::release(FK_Key k) noexcept {
    if ( k != FK_Key::Unknown ) m_keys[k] = false;
}

