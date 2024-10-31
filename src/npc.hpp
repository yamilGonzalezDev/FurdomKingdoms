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
        unsigned int currentFrame = 0;
        float frameDuration = .2f;
        float npcElapsedTime = 0.f;
        float moveSpeed;
        sf::IntRect npcWalk[15];
        sf::Texture texture;
        b2Body* npcBody;
        b2Vec2 movement;
        void loadTextures();
        NpcState state;
    public:
        sf::RectangleShape npcHitBox;
        sf::Vector2f spritePos;
        sf::Sprite sprite;
        void npcMove(float);
        void updateAnimation(float);
        void walkAnimation(float);
        Npc(b2World*, float, float);
        virtual ~Npc();
};

#endif // NPC_H
