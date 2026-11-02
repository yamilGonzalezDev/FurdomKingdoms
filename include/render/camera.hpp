#pragma once

#include <unordered_map>
#include "input/keyboard.hpp"
#include "SFML/Graphics/View.hpp"
#include "utils/vec2.hpp"

struct FK_Keyboard;
struct CameraTarget;
namespace Facade { struct Window; }

enum class CameraMode {
    FREE,
    FOLLOW,
    FOLLOWPLAYER,
    FIXED,
    TEST
};

struct Camera {
    explicit Camera      (float, float, float, float);
    void update          (float);
    void setWindow       (Facade::Window*);
    void setKeyboard     (const FK_Keyboard*);
    void setTarget       (CameraTarget*);
    void setFollowPlayer (CameraTarget*);
    void setMode         (CameraMode);
    void zoomIn          (float);
    void zoomOut         (float);
    void add             ();
    void sub             ();
    void setFixedPosition(const Vec2f&);

private:
    using Behavior = void (Camera::*)(float);

    void zoom              (float);
    void freeCamera        (float);
    void fixedCamera       (float);
    void followCamera      (float);
    void followPlayerCamera(float);
    void setCenter         (float, float);
    void move              (float, float) noexcept;

    std::unordered_map<CameraMode, Behavior> modes {
        { CameraMode::FREE,         &Camera::freeCamera         },
        { CameraMode::FIXED,        &Camera::fixedCamera        },
        { CameraMode::FOLLOW,       &Camera::followCamera       },
        { CameraMode::FOLLOWPLAYER, &Camera::followPlayerCamera }
    };
    Vec2f              m_offset        = {0.f, 60.f}
                     , m_startPos      = {}
                     , m_endPos        = {}
                     , m_startSize     = {}
                     , m_endSize       = {}
                     , defaultSize     = {};
    sf::View           m_view          = {};
    const FK_Keyboard* m_keyboard_ptr  = nullptr;
    Facade::Window*    m_window        = nullptr;
    CameraTarget*      m_target        = nullptr;
    CameraMode         m_currentMode   = CameraMode::FREE;
    const float        m_vel           = 500.f
                     , m_factor        = 0.95f
                     , m_PPM           = 30.f;
    float              elapsed         = 0.f
                     , startZoom       = 0.f
                     , endZoom         = 0.f
                     , duration        = 0.f;
    bool               m_canAccumulate = false;
};
