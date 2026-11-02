#pragma once

#include "SFML/Graphics/Color.hpp"
#include "box2d/box2d.h"

namespace Facade { struct Window; }

class FooDraw : public b2Draw {
public:
    FooDraw();
    void DrawPolygon(const b2Vec2*, int32, const b2Color&) final;
    void DrawSolidPolygon(const b2Vec2*, int32, const b2Color&) final;
    void DrawCircle(const b2Vec2&, float, const b2Color&) final;
    void DrawSolidCircle(const b2Vec2&, float, const b2Vec2&, const b2Color&) final;
    void DrawSegment(const b2Vec2&, const b2Vec2&, const b2Color&) final;
    void DrawTransform(const b2Transform&) final;
    void DrawPoint(const b2Vec2&, float, const b2Color&);
    void setWindow(Facade::Window*);
    ~FooDraw() = default;;
private:
    Facade::Window* m_window = nullptr;

    sf::Color ConvertColor(const b2Color& color) {
        return sf::Color(static_cast<sf::Uint8>(color.r * 255),
                         static_cast<sf::Uint8>(color.g * 255),
                         static_cast<sf::Uint8>(color.b * 255));
    }
};
