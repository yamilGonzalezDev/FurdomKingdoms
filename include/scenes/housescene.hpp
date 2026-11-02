#pragma once

#include "scenes/scene.hpp"
#include "events/sensorobserver.hpp"
#include "physics/physicsfactory.hpp"
#include "render/spritemanager.hpp"
#include "render/parallaxlayer.hpp"
#include "render/layer.hpp"
#include <array>
#include <memory>

class  b2Body;
struct PlayerAnimations;
struct PhysicsWorld;
struct Player;
struct Camera;

struct HouseScene : public Scene, public SensorObserver {
    HouseScene (Facade::Window*);
    void render(     ) final;
    void update(float) final;
    ~HouseScene();
private:
    using Bounds = std::unique_ptr<Collidable>;
    void resizeBound   (b2Body&, float, float    );
    void setKeyboard   (const FK_Keyboard&       ) final;
    void setWindow     (Facade::Window*          ) final;
    void sensorNotify  (PortalID                 ) final;
    void handleInput   (const FK_Keyboard&, float) final;
    void setInputMap   (const InputMap&          ) final;
    void notify        (                         ) final;
    void loadTextures  (                         );
    void loadPhysics   (                         );
    void loadAnimations(                         );
    void startCinematic(                         );
    std::unique_ptr<Player          > m_player;
    std::unique_ptr<PhysicsWorld    > m_phyworld;
    std::unique_ptr<Camera          > m_camera;
    std::unique_ptr<PlayerAnimations> m_playerAnims;
    std::array<SpriteManager, 1 > sprman {};
    ParallaxLayer p_layer1
                , p_layer2
                , p_layer3
                , p_layer4
                , p_layer5;
    Layer<1> structures;
    Layer<2> furniture;
    Layer<1> decorations;
    Layer<1> entities;
    b2Body* body_to_move = nullptr;
    float debugWidth  = 7.37985f //50.f / 30.f
        , debugHeight = 0.1f     //37.f / 30.f;
        , accumulator = 0.f
        , resizeTimer = 0.05f;
};
