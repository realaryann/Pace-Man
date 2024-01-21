#include "paceman.h"
#include "red_ghost.h"

void Red::display(sf::RenderWindow& window)
{
    sf::CircleShape Red(10.f);
    Red.setFillColor(sf::Color::Red);
    sf::Vector2f display_position;
    display_position.x = coord.x * 20.5;
    display_position.y = coord.y * 20.6;
    Red.setPosition(display_position);
    window.draw(Red);
}

void Red::exit_house()
{
    swap(world[coord.y][coord.x], world[9][17]);
    world[10][17] = new Wall(17, 10, world);
    coord.y = 9;
    coord.x = 17;
    exithouse = true;
}

void Red::move()
{
    //Move randomly, But change speeds at random times also, making this ghost the ghost of unpredictibility
    //start here
    srand(time(NULL));
    int choice = rand() % 5;
    switch (choice)
    {
    case UP:
        if ((coord.y > 0) && (world[coord.y - 1][coord.x]->who() != WALL))
        {         
            if ((world[coord.y - 1][coord.x]->who() == PLAYER))
            {
                return;
            }
            swap(world[coord.y][coord.x], world[coord.y - 1][coord.x]);
            coord.y--;
        }
        break;
    case LEFT:
        if ((coord.x > 0) && (world[coord.y][coord.x - 1]->who() != WALL))
        {
            if ((world[coord.y][coord.x - 1]->who() == PLAYER))
            {
                return;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x - 1]);
            coord.x--;
            
        }
        break;
    case RIGHT:
        if ((coord.x + 1 < BOARD_WIDTH) && (world[coord.y][coord.x + 1]->who() != WALL))
        {
            if ((world[coord.y][coord.x + 1]->who() == PLAYER))
            {
                return;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x + 1]);
            coord.x++;
        }
        break;
    case DOWN:
        if ((coord.y + 1 < BOARD_HEIGHT) && (world[coord.y + 1][coord.x]->who() != WALL))
        {
            if ((world[coord.y + 1][coord.x]->who() == PLAYER))
            {
                return;
            }
            swap(world[coord.y][coord.x], world[coord.y + 1][coord.x]);
            coord.y++;
        }
        break;
    }
}

Object_type Red::who()
{
    return RED_GHOST;
}