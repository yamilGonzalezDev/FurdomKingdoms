#include "npc.hpp"

Npc::Npc(b2World* world, float x, float y)
    : moveSpeed(5.f), movement(b2Vec2(0.f, 0.f))
{
    loadTextures();
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
}

void Npc::npcMove(float deltaTime)
{
    if(rand() % 2 == 0)
    {
        movement.x = -moveSpeed;
        walkAnimation(deltaTime);
    }
    else
    {
        movement.x = moveSpeed;
        walkAnimation(deltaTime);
    }

    npcBody->SetLinearVelocity(movement);
    updateAnimation(deltaTime);
}

void Npc::walkAnimation(float deltaTime)
{
    npcElapsedTime = npcElapsedTime + deltaTime;
    if(frameDuration >= frameDuration)
    {
        currentFrame = (currentFrame + 1) % 15;
        sprite.setTextureRect(npcWalk[currentFrame]);
        npcElapsedTime = 0.f;
    }
}

void Npc::updateAnimation(float deltaTime)
{
    npcHitBox.setSize(sf::Vector2f(40.f, 56.f));
    spritePos = sf::Vector2f(npcBody->GetPosition().x, npcBody->GetPosition().y);
    npcHitBox.setPosition(spritePos);
    sprite.setPosition(spritePos);
}

Npc::~Npc()
{

}
