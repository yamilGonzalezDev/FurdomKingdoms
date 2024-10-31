#include "collisions.hpp"
#include "player.hpp"
#include "scene.hpp"

void Collision::BeginContact(b2Contact* contact)
{
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    std::cout << "fA es: " << fA->GetBody()->GetUserData().pointer << std::endl;
    std::cout << "fB es: " << fB->GetBody()->GetUserData().pointer << std::endl;

    //fB->GetBody()->SetU

    /*Player* player = nullptr;
    Ground* ground = nullptr;



    player = reinterpret_cast<Player*>(fA->GetBody()->GetUserData().pointer);
    ground = reinterpret_cast<Ground*>(fB->GetBody()->GetUserData().pointer);

    std::cout << "Player en BeginContact: " << player << std::endl;

    if(player != nullptr && ground != nullptr)
    {
        std::cout << "Contacto" << std::endl;
        player->setIsOnGround(true);
        return;
    }

    player = nullptr;
    ground = nullptr;

    player = reinterpret_cast<Player*>(fB->GetBody()->GetUserData().pointer);
    ground = reinterpret_cast<Ground*>(fA->GetBody()->GetUserData().pointer);

    if(player != nullptr && ground != nullptr)
    {
        std::cout << "Contacto" << std::endl;
        player->setIsOnGround(true);
    }*/
}

void Collision::EndContact(b2Contact* contact)
{
    /*b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    Player* player = nullptr;
    Ground* ground = nullptr;

    player = reinterpret_cast<Player*>(fA->GetBody()->GetUserData().pointer);
    ground = reinterpret_cast<Ground*>(fB->GetBody()->GetUserData().pointer);

    if(player != nullptr && ground != nullptr)
    {
        std::cout << "Descontacto" << std::endl;
        player->setIsOnGround(false);
        return;
    }

    player = nullptr;
    ground = nullptr;

    player = reinterpret_cast<Player*>(fB->GetBody()->GetUserData().pointer);
    ground = reinterpret_cast<Ground*>(fA->GetBody()->GetUserData().pointer);

    if(player != nullptr && ground != nullptr)
    {
        std::cout << "Descontacto" << std::endl;
        player->setIsOnGround(false);
    }*/
}
