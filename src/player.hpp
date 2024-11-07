#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "entity.hpp"

enum class PlayerState
{
    Idle,
    Running,
    Jumping,
    Falling,
    Attacking
};

class Player
{
    private:
        const int CHARACTERWIDTH = 50;
        const int CHARACTERHEIGTH = 37;
        const float PIXELS_PER_METER = 30.f;
        PlayerState playerState;
        int currentFrame = 0;
        float moveSpeed;
        float elapsedTime = 0.0f;
        float frameDuration = 0.15f;
        bool isJumping;
        bool isOnGround;
        bool hit = false;
        bool isMoving = false;
        bool isAttacking;
        b2Vec2 velocity;

    public:
        b2Body* playerBody = nullptr;
        sf::RectangleShape* playerHitbox;
        sf::Image bg;
        sf::Sprite testSprite;
        sf::Sprite bgSprite;
        sf::Sprite sprite;
        sf::Texture bgTexture;
        sf::Texture texture;
        std::vector<sf::IntRect> playerRun;
        std::vector<sf::IntRect> playerIdle;
        std::vector<sf::IntRect> playerJump;
        std::vector<sf::IntRect> playerFall;
        std::vector<sf::IntRect> playerAttack1;
        std::vector<sf::IntRect>* currentAnimation;
        sf::Vector2f getPos();
        sf::Music edificio;
        Player();
        bool loadTextures();
        void test(float);
        void updatePhysics();
        void setIsJumping(bool);
        void runAnimation(float);
        void setIsOnGround(bool);
        void idleAnimation(float);
        void keyboardInput(float);
        void switchState(PlayerState);
        void createPlayer(b2World*, float, float);
        void setAnimation(std::vector<sf::IntRect>*);
        void updateAnimation(float);
        bool getIsOnGround();
        PlayerState getPlayerState();
};

#endif // PLAYER_HPP_INCLUDED
