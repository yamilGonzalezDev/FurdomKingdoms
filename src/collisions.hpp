#ifndef COLLISIONS_HPP_INCLUDED
#define COLLISIONS_HPP_INCLUDED

#include <box2d/box2d.h>
#include <iostream>

class Collision : public b2ContactListener
{
    public:
        void BeginContact(b2Contact* contact)override;
        void EndContact(b2Contact* contact)override;
};

#endif // COLLISIONS_HPP_INCLUDED
