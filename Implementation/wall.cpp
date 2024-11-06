#include "wall.h"

Object_type Wall::who()
{
    return WALL;
}

void Wall::display(sf::RenderWindow& window)
{
    sf::Vector2f v(20.2, 20.4);
    sf::RectangleShape wall(v);
    wall.setFillColor(sf::Color::Blue);
    wall.setPosition(20.5 * coord.x, 20.5 * coord.y);
    window.draw(wall);
}