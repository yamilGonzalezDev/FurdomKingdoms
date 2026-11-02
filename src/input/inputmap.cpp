#include "input/inputmap.hpp"
#include "input/intent.hpp"

void
InputMap::bind(Action a, FK_Keyboard::FK_Key k) noexcept {
    m_keysmap[to_size_t(a)] = k;
}
FK_Keyboard::FK_Key
InputMap::key (Action a) const noexcept {
    return m_keysmap[to_size_t(a)];
}

Intent
buildIntent(const FK_Keyboard& kb, const InputMap& map) noexcept {
    Intent in;
    in.moveX = (kb.isKeyPressed(map.key(Action::Right)) ? 1.f : 0.f)
             - (kb.isKeyPressed(map.key(Action::Left )) ? 1.f : 0.f);
    in.jump  =  kb.justPressed (map.key(Action::Jump ));
    return in;
}
