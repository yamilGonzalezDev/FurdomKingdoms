#ifndef LOADTILES_HPP_INCLUDED
#define LOADTILES_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct TileSet
{
    sf::Texture texture;
    std::vector<sf::IntRect> tiles;

    bool setTileSet(std::string, int, int);
    void draw(sf::RenderWindow&, int[], int, int);
};

#endif // LOADTILES_HPP_INCLUDED
