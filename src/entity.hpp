#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>

typedef struct
{
    int kind;
    int index;
    void* object;
} UserdataTag;

const int PLAYER = 1;

void initBody(b2Body*, int, int, void*);

class Entity
{
    public:
        Entity();
        virtual ~Entity() = default;

        virtual void updateAnimation(float deltaTime);
        void switchAnimation(sf::IntRect* animationFrames, int numFrames);
        virtual void move(float deltaX, float deltaY);
        virtual void updatePhysics();
        void setHitbox(sf::RectangleShape* newHitbox);
        virtual void switchState(int newState);
};

#endif // ENTITY_HPP_INCLUDED
