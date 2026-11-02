#pragma once

#include "input/keyboard.hpp"
#include "utils/cast.hpp"
#include <cstddef>
#include <array>

struct Intent;

enum class Action : std::size_t {
      Left
    , Right
    , Jump
    , Pause
    , COUNT
};

struct InputMap {
    void bind(Action, FK_Keyboard::FK_Key) noexcept;
    FK_Keyboard::FK_Key key (Action) const noexcept;
private:
    std::array<FK_Keyboard::FK_Key, to_size_t(Action::COUNT)> m_keysmap{};
};

Intent buildIntent(const FK_Keyboard&, const InputMap&) noexcept;
