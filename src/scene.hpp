#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "npc.hpp"
#include "globals.hpp"
#include "collisions.hpp"
#include "player.hpp"

class Scene
{
    protected:
        const float WIDTH = 1366;
        const float HEIGHT = 768;
    public:
        virtual ~Scene(){}

        virtual void init() = 0;

        virtual void update(float) = 0;

        virtual void render(sf::RenderWindow&) = 0;

        virtual void cleanup() = 0;

        virtual bool shouldTransition() = 0;
};

class MenuScene : public Scene
{
    public:
        MenuScene();
        void init() override;
        void update(float) override;
        void render(sf::RenderWindow&) override;
        void cleanup() override;
        bool shouldTransition() override;
        sf::Sprite background;
        sf::Texture backgroundTexture;
    private:
};

class HouseScene : public Scene
{
    public:
        void init() override;
        void update(float) override;
        void render(sf::RenderWindow&) override;
        void cleanup() override;
        bool shouldTransition() override;
        sf::Sprite background;
        sf::Texture backgroundTexture;
    private:
};

class Ciudad
{

};

#endif // SCENE_HPP_INCLUDED
