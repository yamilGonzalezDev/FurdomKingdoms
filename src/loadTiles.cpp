#include "loadTiles.hpp"
#include <iostream>

bool TileSet::setTileSet(std::string filename, int columns, int rows)
{
    if(!texture.loadFromFile(filename))
    {
        return false;
    }

    const int tileWidth = 16;
    const int tileHeight = 16;
    columns = 3;
    rows = 5;

    for(int y = 0; y < rows; ++y)
    {
        for(int x = 0; x < columns; ++x)
        {
            tiles.push_back(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
        }
    }

    return true;
}



void TileSet::draw(sf::RenderWindow& window, int v[], int mapWidth, int mapHeight)
{
    for(int i = 0; i < 175; i++)
    {
        for(int y = 0; y < mapHeight; ++y)
        {
            for(int x = 0; x < mapWidth; ++x)
            {
                int tileIndex = v[i];

                if (tileIndex < 0 || tileIndex >= static_cast<int>(tiles.size())) {
                    std::cerr << "Error: Índice de tile fuera de límites: " << std::endl;
                }
                else if(tileIndex < static_cast<int>(tiles.size()))
                {
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setTextureRect(tiles[tileIndex]);
                    sprite.setPosition((x * 16) + 80, (y * 16) + 230);
                    window.draw(sprite);
                }
            }
        }
    }
}
