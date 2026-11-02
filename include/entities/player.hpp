#pragma once

#include "entities/entity.hpp"
#include "components/jumpcomponent.hpp"

struct Intent;
struct PlayerAnimations;
struct Animation;

enum class Direction : signed char {
      Left  = -1
    , Right =  1
};

struct Player : public Entity {
    ~Player() = default;
    CollidableType const& getCollidableType() const noexcept final;
    void setAnimations(const PlayerAnimations*) noexcept;
    void handle(const Intent&) noexcept;
    void update(float)         noexcept;
    void face(Direction) noexcept;
    JumpComponent jumpcmp{};
private:
    using StateFunc   = void (Player::*)(const Intent&);
    StateFunc m_state = &Player::ground;
    Direction m_direction = Direction::Right;

    void ground(const Intent&) noexcept;
    void jump  (const Intent&) noexcept;
    void fall  (const Intent&) noexcept;
    void attack(const Intent&) noexcept;
    void death (const Intent&) noexcept;

    void changeState    (StateFunc    , const Animation&) noexcept;
    void applyHorizontal(const Intent&, float)            noexcept;

    const PlayerAnimations* m_animations            = nullptr;
    static constexpr CollidableType m_colision_type = CollidableType::PLAYER;
};
