#include "scenes/testscene.hpp"
#include "input/keyboard.hpp"
////////////////////////////////////////////////////////////////////////////////
//
// TODO: Make physics create by an interface instead of by classes
//       like Floor or wall
//
// WARNING: REMOVE #include "entities/bounds.hpp"!!!!!
//
#include "entities/enemy.hpp"

////////////////////////////////////////////////////////////////////////////////
//
// TEST SCENE
//
TestScene::TestScene( Facade::Window* window )
    : world    (std::make_unique<b2World       >(b2Vec2(0.f, 9.8f)))
    , factory  (std::make_unique<PhysicsFactory>( *( world.get() ) ))
    , player   (std::make_unique<Player        >())
    , collision(std::make_unique<Collision     >())
    , camera{0.f, 0.f, 482.f, 271.f} {
    setWindow(window);
    fooDraw.SetFlags(b2Draw::e_shapeBit);
    world->SetDebugDraw(&fooDraw);
    world->SetContactListener(collision.get());
}
TestScene::~TestScene() = default;
void
TestScene::update( float dt ) {
    accumulator += dt;
    camera.update(dt);
}

void
TestScene::render() {
    world->DebugDraw();
}

void
TestScene::setWindow( Facade::Window* window ) {
    m_window = window;
    fooDraw.setWindow(window);
    camera .setWindow(window);
}

void
TestScene::handleInput( const FK_Keyboard& keyboard, float dt ) {
    using Key = FK_Keyboard::FK_Key;
    static const float vel = 5.f;
    ////////////////////////////////////////////////////////////////////////////////
    //
    // PLAYER MOVEMENT
    //
    auto& player_ptr = *(player->body().body());
    auto& gravity = player_ptr.GetLinearVelocity().y;
    player_ptr.SetLinearVelocity({0.f, gravity});
    if (keyboard.isKeyPressed(Key::A     )) player_ptr.SetLinearVelocity({-vel, gravity});
    if (keyboard.isKeyPressed(Key::D     )) player_ptr.SetLinearVelocity({ vel, gravity});
    if (keyboard.isKeyPressed(Key::Space ) && player->jumpcmp.getIsOnGround()) {
        player_ptr.ApplyLinearImpulse(
                b2Vec2(0, -player_ptr.GetMass() * 5.f)
            ,   player_ptr.GetWorldCenter()
            ,   true
        );
    }
}
