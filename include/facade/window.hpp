#pragma once

#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window.hpp"
#include <cstddef>
#include <memory>
#include <string>

namespace Facade {

struct Window {
    Window();
    Window(float, float, std::string);
    ~Window();
    sf::View defaultView();
    bool isOpen() const noexcept;
    bool pollEvent(sf::Event&) const noexcept;
    void clear();
    void draw(const sf::Text&);
    void draw(const sf::Sprite&);
    void draw(const sf::Drawable&);
    void draw(const sf::RectangleShape&);
    void createWindow(float, float, std::string);
    void draw(const sf::Vertex*, std::size_t, sf::PrimitiveType);
    void display();
    void setFramerateLimit(int limit);
    void setView(sf::View view);
    void close() noexcept;
    void setSize(unsigned int&, unsigned int&);
    sf::View getView() const;
    sf::Vector2u getSize() const;
private:
    std::unique_ptr<sf::RenderWindow> m_window{};
};

} /// Facade namespace
