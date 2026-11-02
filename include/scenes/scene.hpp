#pragma once

#include "render/texturemanager.hpp"
#include "events/sceneobserver.hpp"
#include "render/renderable.hpp"
#include "render/animator.hpp"
#include <memory>

struct FK_Keyboard;
struct InputMap;

struct Scene : public SceneObserver, public SceneSubject, public Renderable {
    Scene() {}
    virtual ~Scene() = default;
    virtual void render()      = 0;
    virtual void update(float) = 0;
    virtual void handleInput(const FK_Keyboard&, float) {};
    virtual void setKeyboard(const FK_Keyboard&)        {};
    virtual void setInputMap(const InputMap&)           {};
protected:
    TextureManager texturemanager;
    const InputMap* m_inputMap = nullptr;
    const float WIDTH    = 1366;
    const float HEIGHT   = 768;
};
