#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <iostream>

#include "enemy.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "collisions.hpp"
#include "loadTiles.hpp"
#include "npc.hpp"

class Game
{
    private:
        const float pixels_per_meter = 30.0f;
        const float WIDTH = 1366;
        const float HEIGHT = 768;
        float originalVolume = 1.f;
        float timeStep = 1.f/60.f;
        int velocityIterations = 8;
        int positionIterations = 3;
        sf::Vector2f rectPos;
        b2Vec2 bodyPos;
        b2Vec2 gravity;
        Player* player;
        Npc* npc;
        Collision* collisionCheck;

    public:
        Game();
        ~Game();
        sf::RectangleShape* groundShape;
        b2World* world;
        b2BodyDef playerBodyDef;
        b2Body* playerBody;
        b2PolygonShape playerBox;
        sf::RenderWindow window;
        sf::View view;
        sf::Music music;
        sf::Clock clock;

        void gameEvents();
        void createGround(float, float, float, float);
        void createPlayer();
        void destroyBody(b2Body*);
};

#endif // GAME_HPP_INCLUDED
