#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>

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
        int currentRunFrame = 0;
        int currentIdleFrame = 0;
        int currentJumpFrame = 0;
        int currentFallFrame = 0;
        int currentSlideFrame = 0;
        int currentAttackFrame = 0;
        float moveSpeed;
        float frameDuration = 0.1f;
        float elapsedRunTime = 0.0f;
        float elapsedIdleTime = 0.0f;
        float elapsedFallTime = 0.0f;
        float elapsedJumpTime = 0.0f;
        float elapsedSlideTime = 0.0f;
        float elapsedAttackTime = 0.0f;
        float frameDurationIdle = 0.2f;
        bool isJumping;
        bool isOnGround;
        bool hit = false;
        bool isMoving = false;
        bool isAttacking = false;
        b2Vec2 velocity;

    public:
        b2Body* playerBody = nullptr;
        sf::RectangleShape* playerHitbox;
        sf::Image bg;
        sf::Sprite testSprite;
        sf::Sprite bgSprite;
        sf::Sprite playerSprite;
        sf::Texture bgTexture;
        sf::Texture playerTexture;
        sf::IntRect playerRun[6];
        sf::IntRect playerFall[2];
        sf::IntRect playerJump[8];
        sf::IntRect playerIdle[4];
        sf::IntRect playerSlide[4];
        sf::IntRect playerAttack1[5];
        sf::Vector2f getPos();
        sf::Music edificio;
        Player();
        bool loadTextures();
        void run(float);
        void jump(float);
        void fall(float);
        void idle(float);
        void test(float);
        void updatePhysics();
        void setIsOnGround(bool);
        void runAnimation(float);
        void idleAnimation(float);
        void keyboardInput(float);
        void attack(float);
        void switchState(PlayerState);
        void createPlayer(b2World*, float, float);
        void updateAnimation(float);
        bool getIsOnGround();
        PlayerState getPlayerState();
};

#endif // PLAYER_HPP_INCLUDED
