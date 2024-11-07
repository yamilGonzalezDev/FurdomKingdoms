#ifndef DIRECTOR_HPP_INCLUDED
#define DIRECTOR_HPP_INCLUDED

#include <box2d/box2d.h>
#include "npc.hpp"
#include "globals.hpp"
#include "collisions.hpp"
#include "player.hpp"
#include "scene.hpp"

enum class SceneState
{
    MainMenu,
    House,
    Pause
};

class Director
{
    public:
        Director();
        ~Director();
        void run();
        void switchScene(SceneState newState);

    private:
        sf::RenderWindow window;
        sf::View view;
        sf::Clock clock;
        SceneState nextScene;
        SceneState currentSceneState;
        bool start;
        bool drawPlayer;
        bool transitioning;
        float transitionTime;
        float maxTransitionTime;

        b2World* world;
        b2Vec2 gravity;
        Collision* collisionCheck;

//        Npc* npc;
        Ground* ground;
        Player* player;
        MenuScene* menu;
        HouseScene* house;
        Scene* currentScene;

        const float WIDTH = 1366;
        const float HEIGHT = 768;
        const float FLOORHEIGHT = 528.f;

        void init();
        void render();
        void initMenuScene();
        void initHouseScene();
        void update(float deltaTime);
        void transition(float deltaTime);
        void updateScene(float deltaTime);
};

#endif // DIRECTOR_HPP_INCLUDED
