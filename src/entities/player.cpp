#include "entities/player.hpp"
#include "input/intent.hpp"
#include "render/playeranimations.hpp"
#include <iostream>

namespace {
    constexpr float RUN_SPEED  = 5.f;
    constexpr float AIR_SPEED  = 4.f;
    constexpr float JUMP_SPEED = 5.f;
}

void
Player::update(float dt) noexcept {
    animator.update(dt);
}

void
Player::setAnimations(const PlayerAnimations* animations) noexcept {
    m_animations = animations;
}

void
Player::handle(const Intent& in) noexcept {
    (this->*m_state)(in);
}

void
Player::changeState(StateFunc next, const Animation& animation) noexcept {
    m_state = next;
    animator.play(animation);
}

void
Player::applyHorizontal(const Intent& in, float speed) noexcept {
    m_body.setVelocityX(in.moveX * speed);
    if (in.moveX != 0.f) face(in.moveX < 0.f ? Direction::Left : Direction::Right);
}

CollidableType const&
Player::getCollidableType() const noexcept { return m_colision_type; }

void
Player::ground(const Intent& in) noexcept {
    applyHorizontal(in, RUN_SPEED);
    if ( !jumpcmp.getIsOnGround() ) {
        changeState(&Player::fall, m_animations->fall);
        return;
    }
    if ( in.jump ) {
        m_body.setVelocityY(-JUMP_SPEED);
        changeState(&Player::jump, m_animations->jump);
        return;
    }
    animator.play( in.moveX != 0.f ? m_animations->run : m_animations->idle );
}
void
Player::jump(const Intent& in) noexcept {
    applyHorizontal(in, AIR_SPEED);
    if (m_body.velocity().y > 0.f) changeState(&Player::fall, m_animations->fall);
}
void
Player::fall(const Intent& in) noexcept {
    applyHorizontal(in, AIR_SPEED);
    if (jumpcmp.getIsOnGround()) {
        changeState(&Player::ground, in.moveX != 0.f ? m_animations->run : m_animations ->idle );
    }
}
void
Player::attack(const Intent&) noexcept {
    m_body.setVelocityX(0.f);
}
void
Player::death(const Intent&) noexcept {
    m_body.setVelocityX(0.f);
}

void
Player::face(Direction dir) noexcept {
    if (dir == m_direction) return;
    m_direction = dir;
    animator.flipX(dir == Direction::Left);
}
