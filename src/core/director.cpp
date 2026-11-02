#include "core/director.hpp"
#include "core/fade.hpp"
#include "facade/window.hpp"
#include "input/keyboard.hpp"
#include "input/inputmap.hpp"
#include "scenes/scene.hpp"
#include "scenes/portalid.hpp"
#include "scenes/scenefactory.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

Director::Director()
    : m_window  ( std::make_unique<Facade::Window>(1366.f, 768.f, "Furdom Kingdoms") )
    , m_input   ( std::make_unique<FK_Keyboard   >(                                ) )
    , m_inputMap( std::make_unique<InputMap      >(                                ) )
    , m_fade    ( std::make_unique<Fade          >(                                ) )
    , nextPortal(PortalID::TO_MENU) {
    m_fade->setWindow(m_window.get());
    m_fade->end();
    m_window->setFramerateLimit(60);
    changeScene(nextPortal);
    m_inputMap->bind(Action::Left , FK_Keyboard::FK_Key::A    );
    m_inputMap->bind(Action::Right, FK_Keyboard::FK_Key::D    );
    m_inputMap->bind(Action::Jump , FK_Keyboard::FK_Key::Space);
}

Director::~Director() = default;

void
Director::run() {
    while(m_window->isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        updateScene(deltaTime);
        render();
    }
}

void
Director::processEvents() {
    m_input->beginFrame();

    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed ) m_input->press  (event.key.scancode);
        if (event.type == sf::Event::KeyReleased) m_input->release(event.key.scancode);
        if (event.type == sf::Event::LostFocus  ) m_input->releaseAll();
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window->close();
        }
    }
}

void
Director::updateScene(float dt) {
    m_fade->update(dt);
    if (m_fade->fadedOut()) {
        changeScene(nextPortal);
        m_fade->end();
    }
    handleInput(dt);
    m_scene->update(dt);
}

void
Director::render() {
    m_window->clear();
    if ( m_scene != nullptr ) {
        m_scene->render();
    }
    m_fade->render();
    m_window->display();
}

void
Director::changeScene(PortalID nextPortalID) {
    m_scene = SceneFactory::createScene(nextPortalID, m_window.get());
    m_scene->addObserver(this);
    m_scene->setWindow  ( m_window  .get());
    m_scene->setKeyboard(*m_input   .get());
    m_scene->setInputMap(*m_inputMap.get());
}

void
Director::sensorNotify(PortalID portal) {
    nextPortal = portal;
    m_fade->start();
}

void
Director::handleInput(float dt) const noexcept {
    m_scene->handleInput(*m_input.get(), dt);
}
