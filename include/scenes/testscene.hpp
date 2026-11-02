#pragma once

#include "scenes/scene.hpp"
#include "physics/collidable.hpp"
#include "physics/fooDraw.hpp"
#include "physics/physicsfactory.hpp"
#include "entities/player.hpp"
#include "physics/collision.hpp"
#include "render/camera.hpp"
#include "box2d/box2d.h"
#include <memory>
#include <array>

struct TestScene : public Scene {
    TestScene(Facade::Window*);
    void render() final;
    void update(float) final;
    void handleInput(const FK_Keyboard&, float) final;
    ~TestScene();
private:
    using Bounds = std::unique_ptr<Collidable>;
    void sensorNotify(PortalID) final {}
    void setWindow(Facade::Window*) final;
    FooDraw fooDraw;
    std::array<Bounds, 10> bounds {};
    std::unique_ptr<b2World       > world;
    std::unique_ptr<PhysicsFactory> factory;
    std::unique_ptr<Player        > player;
    std::unique_ptr<Enemy         > enemy;
    std::unique_ptr<Collision     > collision;
    Camera camera;
    float accumulator = 0.f;
};
