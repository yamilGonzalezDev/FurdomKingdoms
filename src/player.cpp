#include "player.hpp"

#include <SFML/Audio.hpp>
#include<iostream>

Player::Player()
    : playerState(PlayerState::Idle), moveSpeed(10.f), isJumping(false), isOnGround(true), isMoving(false), isAttacking(false), currentAnimation(&playerIdle)
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
}

bool Player::loadTextures()
{
    if(!texture.loadFromFile("Textures/mainCharacter/charSheetNeeko.png"))
    {
        return false;
    }

    playerIdle =
    {
        sf::IntRect(0, 0, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(50, 0, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(100, 0, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(150, 0, CHARACTERWIDTH, CHARACTERHEIGTH)
    };

    playerRun =
    {
        sf::IntRect(50, 37, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(100, 37, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(150, 37, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(200, 37, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(250, 37, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(300, 37, CHARACTERWIDTH, CHARACTERHEIGTH)
    };

    playerJump =
    {
        sf::IntRect(0, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(50, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(100, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(150, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(200, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(250, 74, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(300, 74, CHARACTERWIDTH, CHARACTERHEIGTH)
    };

    playerFall =
    {
        sf::IntRect(0, 111, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(50, 111, CHARACTERWIDTH, CHARACTERHEIGTH)
    };

    playerAttack1 =
    {
        sf::IntRect(0, 148, CHARACTERWIDTH, CHARACTERHEIGTH),
        sf::IntRect(50, 148, CHARACTERWIDTH, CHARACTERHEIGTH)
    };

    sprite.setTexture(texture);

    return true;
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
    playerHitbox->setFillColor(sf::Color::Transparent);
    playerHitbox->setOutlineColor(sf::Color::White);
    playerHitbox->setOutlineThickness(2.f);

    initBody(playerBody, PLAYER, 0, this);

    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setTextureRect(playerIdle[0]);
}

void Player::setAnimation(std::vector<sf::IntRect>* frames)
{
    currentAnimation = frames;
    currentFrame = 0;
    elapsedTime = 0.f;
}

void Player::switchState(PlayerState state)
{
    if(playerState == state) return;

    playerState = state;

    switch(playerState)
    {
        case PlayerState::Jumping:
            setAnimation(&playerJump);
            //std::cout << "Jump" << std::endl;
            break;
        case PlayerState::Attacking:
            setAnimation(&playerAttack1);
            //std::cout << "Attack" << std::endl;
            break;
        case PlayerState::Running:
            setAnimation(&playerRun);
            //std::cout << "Run" << std::endl;
            break;
        case PlayerState::Falling:
            setAnimation(&playerFall);
            //std::cout << "Falling" << std::endl;
            break;
        case PlayerState::Idle:
            setAnimation(&playerIdle);
            //std::cout << "Idle" << std::endl;
            break;
    }
}

void Player::updateAnimation(float deltaTime)
{
    elapsedTime += deltaTime;
    if(elapsedTime >= frameDuration)
    {
        currentFrame = (currentFrame + 1) % currentAnimation->size();
        sprite.setTextureRect((*currentAnimation)[currentFrame]);
        elapsedTime = 0.f;
    }
}

void Player::keyboardInput(float deltaTime)
{
    velocity = playerBody->GetLinearVelocity();

//    if(isAttacking) return;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking && isOnGround)
    {
        switchState(PlayerState::Attacking);
//        isAttacking = true;
        return;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround)
    {
        velocity.y = -10;
        switchState(PlayerState::Jumping);
        isJumping = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x = -moveSpeed;
        sprite.setScale(-1.5f, 1.5f);
        sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
        isMoving = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x = moveSpeed;
        sprite.setScale(1.5f, 1.5f);
        sprite.setOrigin(0.f, 0.f);
        isMoving = true;
    }
    else if(!isJumping)
    {
        velocity.x = 0;
        isMoving = false;
    }

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

    sprite.setPosition(hitboxPos);

    if(!isOnGround && playerBody->GetLinearVelocity().y > 0)
    {
        switchState(PlayerState::Falling);
    }
    else if(isMoving && !isJumping)
    {
        switchState(PlayerState::Running);
    }
    else if(isOnGround && !isJumping)
    {
        switchState(PlayerState::Idle);
        velocity.x = 0.f;
    }
}

void Player::setIsOnGround(bool v){ isOnGround = v; }

void Player::setIsJumping(bool v){ isJumping = v; }

PlayerState Player::getPlayerState(){ return playerState; }

sf::Vector2f Player::getPos(){ return sprite.getPosition(); }

bool Player::getIsOnGround(){ return isOnGround; }
