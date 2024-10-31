#include "player.hpp"

#include <SFML/Audio.hpp>
#include<iostream>

Player::Player()
    : playerState(PlayerState::Idle), moveSpeed(10.f), isJumping(false), isOnGround(true), isMoving(false)
{
    if(!edificio.openFromFile("Music/jump.wav"))
    {
        return;
    }

    edificio.setVolume(1);

    if(!loadTextures())
    {
        std::cerr << "Error: error al cargar las texturas del personaje" << std::endl;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);
    testSprite.setTexture(playerTexture);
    testSprite.setTextureRect(playerJump[0]);
    testSprite.setScale(1.5f, 1.5f);
}

void Player::createPlayer(b2World* world, float posX, float posY)
{
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(posX / PIXELS_PER_METER, posY / PIXELS_PER_METER);
    playerBody = world->CreateBody(&playerBodyDef);

    b2PolygonShape playerBox;
    playerBox.SetAsBox(CHARACTERWIDTH / PIXELS_PER_METER, 48.f / PIXELS_PER_METER);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    playerBody->CreateFixture(&fixtureDef);

    playerHitbox = new sf::RectangleShape(sf::Vector2f(33.f, 48.f));
    playerHitbox->setOutlineColor(sf::Color::White);
    playerHitbox->setOutlineThickness(0.5f);

    playerBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    std::cout << "GetUserData().pointer del personaje: " << playerBody->GetUserData().pointer << std::endl;

    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(1.5f, 1.5f);
    playerSprite.setTextureRect(playerIdle[0]);
}

void Player::switchState(PlayerState state)
{
    if(playerState == state) return;

    switch (playerState)
    {
        case PlayerState::Jumping:
            edificio.stop();
            break;
        case PlayerState::Attacking:
            isAttacking = false;
            break;
        case PlayerState::Running:
            isMoving = false;
            break;
        case PlayerState::Falling:
            elapsedFallTime = 0.0f;
            break;
        case PlayerState::Idle:
            elapsedIdleTime = 0.0f;
            break;
    }

    playerState = state;

    switch (playerState)
    {
        case PlayerState::Jumping:
            currentJumpFrame = 0;
            elapsedJumpTime = 0.0f;
            edificio.play();
            break;
        case PlayerState::Idle:
            currentIdleFrame = 0;
            elapsedIdleTime = 0.0f;
            break;
        case PlayerState::Running:
            currentRunFrame = 0;
            elapsedRunTime = 0.0f;
            isMoving = true;
            break;
        case PlayerState::Falling:
            currentFallFrame = 0;
            elapsedFallTime = 0.0f;
            break;
        case PlayerState::Attacking:
            currentAttackFrame = 0;
            elapsedAttackTime = 0.0f;
            isAttacking = true;
            break;
    }
}

bool Player::loadTextures()
{
    if(!playerTexture.loadFromFile("Textures/mainCharacter/charSheetNeeko.png"))
    {
        return false;
    }

    if(!bg.loadFromFile("Textures/firstLevel/fondo.jpg"))
    {
        return false;
    }

    bgTexture.loadFromImage(bg);

    playerIdle[0] = sf::IntRect(0, 0, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerIdle[1] = sf::IntRect(50, 0, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerIdle[2] = sf::IntRect(100, 0, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerIdle[3] = sf::IntRect(150, 0, CHARACTERWIDTH, CHARACTERHEIGTH);

    playerRun[0] = sf::IntRect(50, 37, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerRun[1] = sf::IntRect(100, 37, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerRun[2] = sf::IntRect(150, 37, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerRun[3] = sf::IntRect(200, 37, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerRun[4] = sf::IntRect(250, 37, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerRun[5] = sf::IntRect(300, 37, CHARACTERWIDTH, CHARACTERHEIGTH);

    playerJump[0] = sf::IntRect(0, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[1] = sf::IntRect(50, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[2] = sf::IntRect(100, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[3] = sf::IntRect(150, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[4] = sf::IntRect(200, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[5] = sf::IntRect(250, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[6] = sf::IntRect(300, 74, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerJump[7] = sf::IntRect(0, 111, CHARACTERWIDTH, CHARACTERHEIGTH);

    playerFall[0] = sf::IntRect(50, 111, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerFall[1] = sf::IntRect(50, 111, CHARACTERWIDTH, CHARACTERHEIGTH);

    playerAttack1[0] = sf::IntRect(0, 222, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerAttack1[1] = sf::IntRect(50, 222, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerAttack1[2] = sf::IntRect(100, 222, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerAttack1[3] = sf::IntRect(150, 222, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerAttack1[4] = sf::IntRect(200, 222, CHARACTERWIDTH, CHARACTERHEIGTH);

    playerSlide[0] = sf::IntRect(150, 111, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerSlide[1] = sf::IntRect(200, 111, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerSlide[2] = sf::IntRect(250, 111, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerSlide[3] = sf::IntRect(300, 111, CHARACTERWIDTH, CHARACTERHEIGTH);
    playerSlide[4] = sf::IntRect(0, 148, CHARACTERWIDTH, CHARACTERHEIGTH);

    return true;
}

void Player::updateAnimation(float deltaTime)
{
    switch(playerState)
    {
        case PlayerState::Jumping:
            jump(deltaTime);
            break;
        case PlayerState::Idle:
            idle(deltaTime);
            break;
        case PlayerState::Running:
            run(deltaTime);
            break;
        case PlayerState::Falling:
            fall(deltaTime);
            break;
        case PlayerState::Attacking:
            attack(deltaTime);
            break;
    }
}

void Player::keyboardInput(float deltaTime)
{
    velocity = playerBody->GetLinearVelocity();

    if(!isOnGround) return;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking && isOnGround)
    {
        switchState(PlayerState::Attacking);
        currentAttackFrame = 0;
        elapsedAttackTime = 0.0f;
        return;
    }

//    if(isAttacking)
//    {
//        return;
//    }
//
//    if(!isAttacking)
//    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround)
        {
            velocity.y = -10;
            switchState(PlayerState::Jumping);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x = -moveSpeed;
            playerSprite.setScale(-1.5f, 1.5f);
            playerSprite.setOrigin(playerSprite.getLocalBounds().width, 0.f);
            switchState(PlayerState::Running);
            isMoving = true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x = moveSpeed;
            playerSprite.setScale(1.5f, 1.5f);
            playerSprite.setOrigin(0.f, 0.f);
            switchState(PlayerState::Running);
            isMoving = true;
        }
        else
        {
            switchState(PlayerState::Idle);
            velocity.x = 0.f;
            isMoving = false;
        }
//    }
    //std::cout << "Velocity X: " << velocity.x << ", Y: " << velocity.y << std::endl;
    playerBody->SetLinearVelocity(velocity);
    updatePhysics();
}

void Player::updatePhysics()
{
    b2Vec2 bodyPos = playerBody->GetPosition();

    playerHitbox->setPosition(bodyPos.x * PIXELS_PER_METER, bodyPos.y * PIXELS_PER_METER);

    sf::Vector2f hitboxPos = playerHitbox->getPosition();

    hitboxPos.x -= 17.f;

    hitboxPos.y -= 7.f;

    playerSprite.setPosition(hitboxPos);
}

void Player::idle(float deltaTime)
{
    elapsedIdleTime += deltaTime;
    if(elapsedIdleTime > frameDurationIdle)
    {
        currentIdleFrame = (currentIdleFrame + 1) % 4;
        playerSprite.setTextureRect(playerIdle[currentIdleFrame]);
        elapsedIdleTime = 0.0f;
    }
}

void Player::run(float deltaTime)
{
    elapsedRunTime += deltaTime;
    if(elapsedRunTime > frameDuration)
    {
        currentRunFrame = (currentRunFrame + 1) % 6;
        playerSprite.setTextureRect(playerRun[currentRunFrame]);
        elapsedRunTime = 0.0f;
    }
}

void Player::jump(float deltaTime)
{
    elapsedJumpTime += deltaTime;
    if(elapsedJumpTime > frameDuration)
    {
        currentJumpFrame = (currentJumpFrame + 1) % 8;
        playerSprite.setTextureRect(playerJump[currentJumpFrame]);
        elapsedJumpTime = 0.0f;
    }
}

void Player::fall(float deltaTime)
{
    elapsedFallTime += deltaTime;
    if(elapsedFallTime > frameDuration)
    {
        currentFallFrame = (currentFallFrame + 1) % 2;
        playerSprite.setTextureRect(playerFall[currentFallFrame]);
        elapsedFallTime = 0.0f;
    }
}

void Player::attack(float deltaTime)
{
    elapsedAttackTime += deltaTime;
    if(elapsedAttackTime > frameDuration)
    {
        currentAttackFrame = (currentAttackFrame + 1) % 5;
        playerSprite.setTextureRect(playerAttack1[currentAttackFrame]);
        elapsedAttackTime = 0.0f;
    }
}

void Player::setIsOnGround(bool v){ isOnGround = v; }

PlayerState Player::getPlayerState(){ return playerState; }

sf::Vector2f Player::getPos(){ return playerSprite.getPosition(); }

bool Player::getIsOnGround(){ return isOnGround; }
