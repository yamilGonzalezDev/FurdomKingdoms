#include "scenes/housescene.hpp"
#include "input/keyboard.hpp"
#include "render/animator.hpp"
#include "utils/vec2.hpp"
#include "render/camera.hpp"
#include "entities/player.hpp"
#include "physics/physicsworld.hpp"
#include "render/playeranimations.hpp"
#include "input/inputmap.hpp"
#include "input/intent.hpp"
#include <memory>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
//
// TODO: Make physics create by an interface instead of by classes
//       like Floor or Wall
//
// WARNING: REMOVE #include "entities/bounds.hpp"!!!!!
//
#include "entities/bounds.hpp"

////////////////////////////////////////////////////////////////////////////////
//
// HOUSE SCENE
//
HouseScene::HouseScene( Facade::Window* window_ptr )
    : m_player     ( std::make_unique<Player          >(                          ) )
    , m_phyworld   ( std::make_unique<PhysicsWorld    >(                          ) )
    , m_camera     ( std::make_unique<Camera          >(431.f, 605.f, 482.f, 271.f) )
    , m_playerAnims( std::make_unique<PlayerAnimations>(                          ) ) {
    setWindow(window_ptr);
    loadAnimations();
    loadTextures  ();
    loadPhysics   ();
    m_camera->setFollowPlayer(m_player.get());
}
HouseScene::~HouseScene() = default;
void
HouseScene::loadPhysics() {
    m_phyworld->createFloor ({7.37985f , 0.1f     }, {19.2167f, 23.1001f});
    m_phyworld->createWall  ({9.03987f , 0.1f     }, {19.2167f, 19.0896f});
    m_phyworld->createWall  ({0.1f     , 1.91333f }, {12.2197f, 21.1061f});
    m_phyworld->createWall  ({0.266668f, 1.11333f }, {26.4347f, 20.2714f});
    m_phyworld->createFloor ({8.99987f , 0.1f     }, {35.5937f, 23.6355f});
    m_phyworld->createSensor({0.679856f, 1.06f    }, {29.6566f, 22.4556f}, *this);
    m_phyworld->createPlayer({0.306668f, 0.593334f}, {13.2788f, 22.4104f}, m_player.get());
    body_to_move  = m_phyworld->createMovableBody({8.99987f , 0.1f}, {35.5937f, 23.6355f});
    auto& fixture = *(body_to_move->GetFixtureList());
    const auto* box = static_cast<const b2PolygonShape*>(fixture.GetShape());
    debugWidth  = box->m_vertices[1].x;
    debugHeight = box->m_vertices[1].y;
}

void
HouseScene::loadTextures() {
    texturemanager.add("houseLayer1", "Textures/houseLevel/layer1.png"           );
    texturemanager.add("houseLayer2", "Textures/houseLevel/layer2.png"           );
    texturemanager.add("houseLayer3", "Textures/houseLevel/layer3.png"           );
    texturemanager.add("houseLayer4", "Textures/houseLevel/layer4.png"           );
    texturemanager.add("houseLayer5", "Textures/houseLevel/layer5.png"           );
    texturemanager.add("house"      , "Textures/houseLevel/house.png"            );
    texturemanager.add("table"      , "Textures/houseLevel/table.png"            );
    texturemanager.add("bed"        , "Textures/houseLevel/bed.png"              );
    texturemanager.add("candle"     , "Textures/houseLevel/candle.png"           );
    texturemanager.add("player"     , "Textures/mainCharacter/charSheetNeeko.png");
    p_layer1.add( texturemanager.getTexture( "houseLayer1" ) );
    p_layer2.add( texturemanager.getTexture( "houseLayer2" ) );
    p_layer3.add( texturemanager.getTexture( "houseLayer3" ) );
    p_layer4.add( texturemanager.getTexture( "houseLayer4" ) );
    p_layer5.add( texturemanager.getTexture( "houseLayer5" ) );
    auto& house_spr  = structures .add( texturemanager.getTexture( "house"  ) );
    auto& table_spr  = furniture  .add( texturemanager.getTexture( "table"  ) );
    auto& bed_spr    = furniture  .add( texturemanager.getTexture( "bed"    ) );
    auto& candle_spr = decorations.add( texturemanager.getTexture( "candle" ) );
    auto& player_spr = entities   .add( texturemanager.getTexture( "player" ) );
    p_layer1  .setScale({1.2f, 1.2f});
    p_layer1  .setFactor( .020f );
    p_layer2  .setFactor( .018f );
    p_layer3  .setFactor( .032f );
    p_layer4  .setFactor( .08f) ;
    p_layer5  .setFactor( .04f) ;
    p_layer1  .setPosition({-100.f, 670.f});
    p_layer2  .setPosition({-100.f, 685.f});
    p_layer3  .setPosition({-100.f, 378.f});
    p_layer4  .setPosition({-100.f, 378.f});
    p_layer5  .setPosition({-100.f, 378.f});
    house_spr .setPosition(  305.f, 514.f );
    table_spr .setPosition(  450.f, 668.f );
    bed_spr   .setPosition(  368.f, 658.f );
    candle_spr.setPosition(  457.f, 648.f );
    player_spr.setPosition(  400.f, 600.f );
    p_layer1  .setTextureRect({ 0, 0, 3000, p_layer1.getTextSize().y });
    p_layer2  .setTextureRect({ 0, 0, 3000, p_layer2.getTextSize().y });
    p_layer3  .setTextureRect({ 0, 0, 3000, p_layer3.getTextSize().y });
    p_layer4  .setTextureRect({ 0, 0, 3000, p_layer4.getTextSize().y });
    p_layer5  .setTextureRect({ 0, 0, 3000, p_layer5.getTextSize().y });
    candle_spr.setTextureRect(sf::IntRect(0, 0, 12, 20));

    m_player->setAnimations(m_playerAnims.get());
    m_player->animator.setSprite(player_spr);
    m_player->animator.play(m_playerAnims->idle);

    sprman[0].set(player_spr, m_player->body());
}

void
HouseScene::loadAnimations() {
    const Vec2i CHARACTER_SIZE = {50, 37};
    m_playerAnims->idle = Animation {
        { sf::IntRect(  0, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect( 50, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(150, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.15f
    };
    m_playerAnims->run = Animation {
        { sf::IntRect( 50, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(150, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(200, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(250, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(300, 37, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.1f
    };
    m_playerAnims->jump = Animation {
        { sf::IntRect(  0,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect( 50,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(150,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(200,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(250,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(300,  74, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(  0, 111, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.082f
    };
    m_playerAnims->fall = Animation{
        { sf::IntRect( 50, 111, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100, 111, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.2f
    };
    m_playerAnims->attack = Animation{
        { sf::IntRect(  0, 222, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect( 50, 222, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100, 222, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(150, 222, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(200, 222, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.08f
    };
    m_playerAnims->death = Animation{
        { sf::IntRect(300, 296, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(  0, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect( 50, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(100, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(150, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(200, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y),
          sf::IntRect(250, 333, CHARACTER_SIZE.x, CHARACTER_SIZE.y) }, 0.08f
    };
}

void
HouseScene::update(float dt) {
    resizeTimer -= dt;

    if (resizeTimer <= 0.f) {
        resizeTimer = 0.05f;
    }

    m_phyworld->step(dt);

    for (auto& spr : sprman) spr.update();

    p_layer5.update();
    p_layer4.update();
    p_layer3.update();
    p_layer2.update();
    p_layer1.update();

    m_player->update(dt);

    m_camera->update(dt);
}

void
HouseScene::render() {
    ////////////////////////////////////////////////////////////////////////////////
    //
    // WARNING!!
    //
    // m_phyworld->render(); IS FOR DEBUG ONLY PURPOSE!! DELETE WHEN RELEASE
    //
    for ( auto& spr : sprman ) spr.render();

    p_layer5   .render();
    p_layer4   .render();
    p_layer3   .render();
    p_layer2   .render();
    structures .render();
    furniture  .render();
    decorations.render();
    entities   .render();
    p_layer1   .render();
    //m_phyworld->render();
}

void
HouseScene::setWindow( Facade::Window* window_ptr ) {
    auto& camera = *(m_camera.get());
    m_window     = window_ptr;

    camera     .setWindow(window_ptr);
    furniture  .setWindow(window_ptr);
    decorations.setWindow(window_ptr);
    structures .setWindow(window_ptr);
    entities   .setWindow(window_ptr);
    p_layer1   .setWindow(window_ptr);
    p_layer2   .setWindow(window_ptr);
    p_layer3   .setWindow(window_ptr);
    p_layer4   .setWindow(window_ptr);
    p_layer5   .setWindow(window_ptr);
    m_phyworld->setWindow(window_ptr);
}

void
HouseScene::resizeBound( b2Body& body, float width, float height ) {
    b2Fixture& old     = *(body.GetFixtureList());
    uintptr_t owner    = old.GetUserData().pointer;
    body.DestroyFixture(&old);

    b2PolygonShape box;
    box.SetAsBox(width, height);

    b2FixtureDef fixtureDef;
    fixtureDef.shape            = &box;
    fixtureDef.userData.pointer = owner;

    body.CreateFixture(&fixtureDef);
}

void
HouseScene::handleInput( const FK_Keyboard& keyboard, float dt ) {
    ////////////////////////////////////////////////////////////////////////////////
    //
    // ALIASES
    //
    using Key        = FK_Keyboard::FK_Key;
    auto& camera     = *(m_camera.get());
    auto& bodyToMove = *(body_to_move);
    auto  pos        = bodyToMove.GetPosition();

    ////////////////////////////////////////////////////////////////////////////////
    //
    // LOCAL VARIABLES
    //
    static float s = 1.f;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // BOUNDING BOX SPEED CONTROL
    //
    if (keyboard.isKeyPressed(Key::Y)) s = 50.f;
    if (keyboard.isKeyPressed(Key::U)) s = 1.f;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // BOUNDING BOX MOVEMENT
    //
    if (keyboard.isKeyPressed(Key::Up   )) bodyToMove.SetTransform({pos.x += ( 0.f * dt), pos.y += (-s   * dt)}, 0.f);
    if (keyboard.isKeyPressed(Key::Down )) bodyToMove.SetTransform({pos.x += ( 0.f * dt), pos.y += ( s   * dt)}, 0.f);
    if (keyboard.isKeyPressed(Key::Left )) bodyToMove.SetTransform({pos.x += (-s   * dt), pos.y += ( 0.f * dt)}, 0.f);
    if (keyboard.isKeyPressed(Key::Right)) bodyToMove.SetTransform({pos.x += ( s   * dt), pos.y += ( 0.f * dt)}, 0.f);
    if (keyboard.isKeyPressed(Key::Enter)) {
        b2Fixture& fixture = *(bodyToMove.GetFixtureList());
        const b2PolygonShape* box = static_cast<const b2PolygonShape*>(fixture.GetShape());
        std::cout << "({" << box->m_vertices[1].x       << "f, " << box->m_vertices[2].y       << "f},"
                  << " {" << bodyToMove.GetPosition().x << "f, " << bodyToMove.GetPosition().y << "f});\n";
    }

    ////////////////////////////////////////////////////////////////////////////////
    //
    // BOUNDING BOX RESIZING
    //
    if (keyboard.isKeyPressed(Key::I)) { debugHeight += 0.02f; resizeBound(bodyToMove, debugWidth, debugHeight); }
    if (keyboard.isKeyPressed(Key::K)) { debugHeight -= 0.02f; resizeBound(bodyToMove, debugWidth, debugHeight); }
    if (keyboard.isKeyPressed(Key::L)) { debugWidth  += 0.02f; resizeBound(bodyToMove, debugWidth, debugHeight); }
    if (keyboard.isKeyPressed(Key::J)) { debugWidth  -= 0.02f; resizeBound(bodyToMove, debugWidth, debugHeight); }

    ////////////////////////////////////////////////////////////////////////////////
    //
    // PLAYER MOVEMENT
    //
    m_player->handle(buildIntent(keyboard, *m_inputMap));

    ////////////////////////////////////////////////////////////////////////////////
    //
    // CAMERA KEYS
    //
    // if (keyboard.isKeyPressed(Key::Z)) camera.zoomIn();
    // if (keyboard.isKeyPressed(Key::X)) camera.zoomOut();
    // if (keyboard.isKeyPressed(Key::C)) camera.print();
    // if (keyboard.isKeyPressed(Key::M)) camera.add();
    // if (keyboard.isKeyPressed(Key::N)) camera.sub();
    // if (keyboard.isKeyPressed(Key::Q)) camera.setTarget(player.get());
    static float acc = 0.f;
    acc+=dt;
    if (acc >= 0.2f){
        if (keyboard.isKeyPressed(Key::Q)) camera.setFollowPlayer(m_player.get());
        if (keyboard.isKeyPressed(Key::E)) {
            camera.setFixedPosition({1500.f, 450.f});
            camera.setMode(CameraMode::FIXED);
        }
        acc = 0.f;
    }
}

void
HouseScene::setKeyboard( const FK_Keyboard& k ) { m_camera->setKeyboard(&k); }

void
HouseScene::setInputMap( const InputMap& im ) { m_inputMap = &im; }

void
HouseScene::notify() { startCinematic(); }

void
HouseScene::startCinematic() {
    m_camera->setFixedPosition({1500.f, 450.f});
    m_camera->setMode(CameraMode::FIXED);
}

void
HouseScene::sensorNotify(PortalID n_p_id) { sensorTrigger(n_p_id); }
