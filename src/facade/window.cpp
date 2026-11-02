#include "facade/window.hpp"

Facade::Window::Window() : m_window(std::make_unique<sf::RenderWindow>()) {}

Facade::Window::Window(float width, float height, std::string title = "Default")
    : m_window(std::make_unique<sf::RenderWindow>()) {
    createWindow(width, height, title);
}
Facade::Window::~Window() { if (m_window && m_window->isOpen()) m_window->close(); }
void
Facade::Window::createWindow(float w, float h, std::string title) { m_window->create(sf::VideoMode(w, h), title); }
bool
Facade::Window::isOpen() const noexcept { return m_window->isOpen(); }
bool
Facade::Window::pollEvent(sf::Event& e) const noexcept { return m_window->pollEvent(e); }
void
Facade::Window::clear() { m_window->clear(); }
sf::View
Facade::Window::defaultView() { return m_window->getDefaultView(); }
void
Facade::Window::draw(const sf::Sprite& sprite)                                        { m_window->draw(sprite);          }
void
Facade::Window::draw(const sf::Text& text)                                            { m_window->draw(text);            }
void
Facade::Window::draw(const sf::RectangleShape& rect)                                  { m_window->draw(rect);            }
void
Facade::Window::draw(const sf::Drawable& drawable)                                    { m_window->draw(drawable);        }
void
Facade::Window::draw(const sf::Vertex* ver, std::size_t num, sf::PrimitiveType lines) { m_window->draw(ver, num, lines); }
void
Facade::Window::close() noexcept { m_window->close(); }
void
Facade::Window::display() { m_window->display(); }
void
Facade::Window::setFramerateLimit(int limit) { m_window->setFramerateLimit(limit); }
void
Facade::Window::setView(sf::View view) { m_window->setView(view); }
void
Facade::Window::setSize(unsigned int& x, unsigned int& y) { m_window->setSize({x, y}); }
sf::View
Facade::Window::getView() const { return m_window->getView(); }
sf::Vector2u
Facade::Window::getSize() const { return m_window->getSize(); }
