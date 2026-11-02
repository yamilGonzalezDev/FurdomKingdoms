#include "physics/collision.hpp"
#include "physics/collidable.hpp"
#include "components/jumpcomponent.hpp"
#include "entities/bounds.hpp"
#include <cassert>

Collision::Collision() {
    beginTable.addMirror<&JumpComponent::onBeginCollision>(CollidableType::JUMPCMP, CollidableType::FLOOR );
    beginTable.addMirror<&Sensor       ::onBeginCollision>(CollidableType::SENSOR , CollidableType::PLAYER);
    beginTable.addMirror<&Portal       ::onBeginCollision>(CollidableType::PORTAL , CollidableType::PLAYER);
    endTable.addMirror  <&JumpComponent::onEndCollision  >(CollidableType::JUMPCMP, CollidableType::FLOOR );
}

void
Collision::BeginContact(b2Contact* contact) {
    auto* colA = reinterpret_cast<Collidable*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* colB = reinterpret_cast<Collidable*>(contact->GetFixtureB()->GetUserData().pointer);

    assert(colA && colB);

    beginTable.solve(*colA, *colB);
}
void
Collision::EndContact(b2Contact* contact) {
    auto* colA = reinterpret_cast<Collidable*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* colB = reinterpret_cast<Collidable*>(contact->GetFixtureB()->GetUserData().pointer);

    assert(colA && colB);

    endTable.solve(*colA, *colB);
}
