#include "npc.hpp"

Npc::Npc(b2World* world, float x, float y)
    : npcSpeed(5.f), movement(b2Vec2(0.f, 0.f))
{
    loadTextures();
//    x = x / PPM;
//    y = y / PPM;
    b2BodyDef npcBodyDef;
    npcBodyDef.type = b2_dynamicBody;
    npcBodyDef.position.Set(x, y);
    npcBody = world->CreateBody(&npcBodyDef);

    b2PolygonShape npcBox;
    npcBox.SetAsBox(40, 56);

    b2FixtureDef npcFixtureDef;
    npcFixtureDef.shape = &npcBox;
    npcFixtureDef.density = 1.f;
    npcFixtureDef.friction = .3f;

    npcBody->CreateFixture(&npcFixtureDef);

    npcHitBox.setFillColor(sf::Color::Transparent);
    npcHitBox.setOutlineColor(sf::Color::Red);
    npcHitBox.setOutlineThickness(.5f);
    sprite.setOrigin(0.f, 0.f);
    sprite.setTexture(texture);
    sprite.setTextureRect(npcWalk[0]);
}

void Npc::updateAnimation(float deltaTime)
{
    switch(npcState)
    {
        case NpcState::Idle:
            idle(deltaTime);
        case NpcState::Walking:
            walk(deltaTime);
    }
}

void Npc::updatePhysics()
{
    npcHitBox.setSize(sf::Vector2f(40.f, 56.f));
    spritePos = sf::Vector2f(npcBody->GetPosition().x * PPM, npcBody->GetPosition().y * PPM);
    npcHitBox.setPosition(spritePos);
    sprite.setPosition(spritePos);
}

void Npc::switchState(NpcState state)
{
    if(npcState == state) return;

    switch(npcState)
    {
        case NpcState::Idle:
            //logic();
            break;
        case NpcState::Walking:
            //logic();
            break;
    }

    npcState = state;

    switch (npcState)
    {
        case NpcState::Idle:
            //logic();
            break;
        case NpcState::Walking:
            //logic();
            break;
    }
}

void Npc::loadTextures()
{
    if(!texture.loadFromFile("Textures/NPCs/npc.png"))
    {
        return;
    }

    for(int i = 0; i < 15; i++)
    {
        npcWalk[i] = sf::IntRect(0, 56 * (i + 1), 40, 56);
    }

    npcIdle = sf::IntRect(0, 0, 40, 56);
}

void Npc::npcMove(float deltaTime)
{
    movement = npcBody->GetLinearVelocity();

    int random = rand() % 2;
    if(random == 0)
    {
        movement.x = -npcSpeed;
        walk(deltaTime);
    }
    else if(random == 1)
    {
        movement.x = npcSpeed;
        walk(deltaTime);
    }
    else
    {
        movement.x = 0.f;
        idle(deltaTime);
    }

    npcBody->SetLinearVelocity(movement);
    updatePhysics();
}

void Npc::walk(float deltaTime)
{
    npcElapsedTime = npcElapsedTime + deltaTime;
    if(npcElapsedTime >= frameDuration)
    {
        currentFrame = (currentFrame + 1) % 15;
        sprite.setTextureRect(npcWalk[currentFrame]);
        npcElapsedTime = 0.f;
    }
}

void Npc::idle(float deltaTime)
{
    sprite.setTextureRect(npcIdle);
}

Npc::~Npc()
{
}
