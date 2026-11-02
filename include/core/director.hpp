#pragma once

#include "events/sceneobserver.hpp"
#include "SFML/System/Clock.hpp"
#include <memory>

namespace Facade { struct Window; }
struct    Scene;
struct    FK_Keyboard;
struct    InputMap;
struct    Fade;

////////////////////////////////////////////////////////////////////////////////
//
// High-level game manager.
//
// Owns the current Scene, input system and global game state
//
struct Director : public SceneObserver {
    ////////////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR AND DESTRUCTOR
    //
    Director();
    ~Director();

    ////////////////////////////////////////////////////////////////////////////////
    //
    // MAIN GAME LOOP
    //
    void run();

private:
    ////////////////////////////////////////////////////////////////////////////////
    //
    // FACADE::WINDOW
    //
    // Owns the only window instance
    //
    std::unique_ptr<Facade::Window> m_window;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // SCENE
    //
    // Owns the current active Scene
    //
    std::unique_ptr<Scene> m_scene;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // KEYBOARD
    //
    // Owns the game input handler (Keyboard only at this point)
    //
    std::unique_ptr<FK_Keyboard> m_input;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // INPUT MAP
    //
    // Owns a map of input keys to handle
    //
    std::unique_ptr<InputMap> m_inputMap;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // FADE
    //
    // Owns handler to transition between scenes with fade in and fade out
    //
    std::unique_ptr<Fade> m_fade;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // CLOCK
    //
    // TODO: Make a facade or an interface to fully delete sf dependencies from this->hpp
    //
    sf::Clock clock;

    ////////////////////////////////////////////////////////////////////////////////
    //
    // PORTALID
    //
    // Stores the next destination requested by the Scene.
    // Initialized with the first destination the player will see, normally the Menu
    //
    PortalID nextPortal;

    void render();
    void updateScene(float);
    void changeScene(PortalID);
    void handleInput(float) const noexcept;
    void sensorNotify(PortalID) final;
    void processEvents();
};
