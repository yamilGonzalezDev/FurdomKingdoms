#include "entity.hpp"
#include <cstring>
#include <iostream>

void initBody(b2Body* body, int entityKind, int index, void* object)
{
    UserdataTag* tag = new UserdataTag{entityKind, index, object};

    b2BodyUserData& ud = body->GetUserData();

    ud.pointer = reinterpret_cast<uintptr_t>(tag);
}
