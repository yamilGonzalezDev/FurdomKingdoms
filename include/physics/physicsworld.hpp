#pragma once

#include "utils/vec2.hpp"
#include <memory>
#include <vector>

class  b2World;
struct FooDraw;
struct Player;
struct Collision;
struct Collidable;
struct SensorObserver;
struct PhysicsFactory;
struct b2Body;
namespace Facade { struct Window; }

struct PhysicsWorld {
    explicit PhysicsWorld();
    ~PhysicsWorld();
    ////////////////////////////////////////////////////////////////////////////////
    //
    // DEBUG AND TEST PURPOSE ONLY!!!
    //
    b2Body* createMovableBody(Vec2f, Vec2f);
    void    createFloor      (Vec2f, Vec2f);
    void    createWall       (Vec2f, Vec2f);
    void    createSensor     (Vec2f, Vec2f, SensorObserver&);
    void    createPlayer     (Vec2f, Vec2f, Player*);
    void    step(float);
    void    render();
    void    setWindow(Facade::Window*);
private:
    template <typename BoundType>
    void create(Vec2f, Vec2f);
    std::unique_ptr<b2World>                 m_world;
    std::unique_ptr<PhysicsFactory>          m_factory;
    std::unique_ptr<Collision>               m_collision;
    std::unique_ptr<FooDraw>                 m_fooDraw;
    std::vector<std::unique_ptr<Collidable>> m_data;
    float                                    m_accumulator{};
    const float                              m_timeStep = 1.f/60.f;
    const int                                m_velIter  = 6
                                           , m_posIter  = 2;
};
