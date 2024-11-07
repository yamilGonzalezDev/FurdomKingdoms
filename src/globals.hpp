#ifndef GLOBALS_HPP
#define GLOBALS_HPP

class Ground
{
    private:
        const float PPM;
    public:
        Ground();
        void createGround(b2World* world, float x, float y, float width, float height)
        {
            b2BodyDef groundBodyDef;
            groundBodyDef.type = b2_staticBody;
            groundBodyDef.position.Set(x / PPM, y / PPM);

            b2Body* groundBody = world->CreateBody(&groundBodyDef);

            b2PolygonShape groundBox;
            groundBox.SetAsBox(width / PPM, height / PPM);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &groundBox;
            fixtureDef.density = 0.f;
            fixtureDef.friction = 0.4f;

            groundBody->CreateFixture(&fixtureDef);

            sf::RectangleShape* groundShape = new sf::RectangleShape(sf::Vector2f(width, height));
            //groundShape->setOrigin(width/2.f, height/2.f);
            groundShape->setPosition(x, y);
            groundShape->setOutlineColor(sf::Color::Red);
            groundShape->setOutlineThickness(0.5f);
            //groundShape->setFillColor(sf::Color::Transparent);

            groundBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
        }
};

#endif
