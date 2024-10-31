#include "scene.hpp"

bool Ground::load(const std::string& tileset, sf::Vector2f tileSize, int tilesCountX)
    {
        if(!m_texture.loadFromFile(tileset))
            return false;

        m_tilesCountX = tilesCountX;

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(tilesCountX * 4);

        for(int i = 0; i < tilesCountX; ++i)
        {
            sf::Vertex* quad = &m_vertices[i * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, 463);  // Arriba izquierda
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, 463);  // Arriba derecha
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, 500);  // Abajo derecha
            quad[3].position = sf::Vector2f(i * tileSize.x, 500);  // Abajo izquierda

            quad[0].texCoords = sf::Vector2f(16, 224);
            quad[1].texCoords = sf::Vector2f(178, 224);
            quad[2].texCoords = sf::Vector2f(178, 255);
            quad[3].texCoords = sf::Vector2f(16, 255);

            tileSize.x = tileSize.x - 2;
        }

        return true;
    }

sf::FloatRect Ground::getBounds()
{
    return sf::FloatRect(0, 463 + 5, m_tilesCountX * 162, 32 - 5);
}
