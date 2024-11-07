#ifndef NPC_HPP
#define NPC_HPP

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

enum class NpcState
{
    Idle,
    Walking
};

class Npc
{
    private:
        const float PPM = 30.f;
        unsigned int currentFrame = 0;
        float frameDuration = .1f;
        float npcElapsedTime = 0.f;
        float npcSpeed;
        sf::IntRect npcIdle;
        sf::IntRect npcWalk[15];
        sf::Texture texture;
        b2Body* npcBody;
        b2Vec2 movement;
        void loadTextures();
        void switchState(NpcState);
        NpcState npcState;
    public:
        sf::RectangleShape npcHitBox;
        sf::Vector2f spritePos;
        sf::Sprite sprite;
        void walk(float);
        void idle(float);
        void npcMove(float);
        void updateAnimation(float);
        void updatePhysics();
        Npc(b2World*, float, float);
        virtual ~Npc();
};

#endif // NPC_H
