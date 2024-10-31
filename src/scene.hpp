#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "game.hpp"

class Ground : public sf::Drawable, public sf::Transformable
{
    public:
        bool load(const std::string& tileset, sf::Vector2f tileSize, int tilesCountX);
        sf::FloatRect getBounds();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();

            states.texture = &m_texture;

            target.draw(m_vertices, states);
        }

        sf::VertexArray m_vertices;
        sf::Texture m_texture;
        int m_tilesCountX;
};

#endif // SCENE_HPP_INCLUDED
