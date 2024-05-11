#include "candy.h"

void Candy::display(sf::RenderWindow& window)
{
    sf::CircleShape candy(2.f);
    candy.setFillColor(sf::Color::White);
    sf::Vector2f display_position;

    display_position.x = coord.x * 21.4;
    display_position.y = coord.y * 21.4;
    candy.setPosition(display_position);
    window.draw(candy);
}

Object_type Candy::who() {
    return CANDY;
}