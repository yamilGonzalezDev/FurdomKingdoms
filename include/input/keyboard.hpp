#pragma once

#include <array>
#include <cstddef>
#include "SFML/Window/Keyboard.hpp"

struct FK_Keyboard {
    using FK_Key = sf::Keyboard::Scancode;

    explicit FK_Keyboard() = default;

    FK_Keyboard(const FK_Keyboard&)            = delete;
    FK_Keyboard(FK_Keyboard&&)                 = delete;
    FK_Keyboard& operator=(const FK_Keyboard&) = delete;
    FK_Keyboard& operator=(FK_Keyboard&&)      = delete;

    void beginFrame() noexcept;
    void releaseAll() noexcept;

    void press  (FK_Key k) noexcept;
    void release(FK_Key k) noexcept;

    bool isKeyPressed(FK_Key k) const noexcept;
    bool justPressed (FK_Key k) const noexcept;
private:
    static constexpr std::size_t COUNT = sf::Keyboard::Scan::ScancodeCount;
    using FK_KeyboardSet = std::array<bool, COUNT>;
    FK_KeyboardSet m_keys{};
    FK_KeyboardSet m_prev{};
};
