#include "paceman.h"
#include "red_ghost.h"

void Red::display(sf::RenderWindow& window)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.045, 0.045);
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    sf::Vector2f display_position;
    display_position.x = coord.x * 21;
    display_position.y = coord.y * 20.6;
    sprite.setPosition(display_position);
    if (dir == LEFT)
    {
        sprite.setScale(-0.05f, 0.05f);
    }
    window.draw(sprite);
}

Coord Red::exit_house()
{
    // Close the gate
    delete world[gate.y][gate.x];
    world[gate.y][gate.x] = new Wall(gate.x, gate.y, world);
    swap(world[coord.y][coord.x], world[6][9]);
    delete world[coord.y][coord.x];
    world[coord.y][coord.x] = new Tile(coord.x, coord.y, world);
    coord.y = 6;
    coord.x = 9;
    exithouse = true;
    return coord;
}

Coord Red::move()
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
            dir = UP;
            if ((world[coord.y - 1][coord.x]->who() == PLAYER))
            {
                world[coord.y - 1][coord.x]->set_lives(world[coord.y - 1][coord.x]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y - 1][coord.x]);
            coord.y--;
        }
        break;
    case LEFT:
        if ((coord.x > 0) && (world[coord.y][coord.x - 1]->who() != WALL))
        {
            dir = LEFT;
            if ((world[coord.y][coord.x - 1]->who() == PLAYER))
            {
                world[coord.y][coord.x - 1]->set_lives(world[coord.y][coord.x - 1]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x - 1]);
            coord.x--;
            
        }
        break;
    case RIGHT:
        if ((coord.x + 1 < BOARD_WIDTH) && (world[coord.y][coord.x + 1]->who() != WALL))
        {
            dir = RIGHT;
            if ((world[coord.y][coord.x + 1]->who() == PLAYER))
            {
                world[coord.y][coord.x + 1]->set_lives(world[coord.y][coord.x + 1]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x + 1]);
            coord.x++;
        }
        break;
    case DOWN:
        if ((coord.y + 1 < BOARD_HEIGHT) && (world[coord.y + 1][coord.x]->who() != WALL))
        {
            dir = DOWN;
            if ((world[coord.y + 1][coord.x]->who() == PLAYER))
            {
                world[coord.y + 1][coord.x]->set_lives(world[coord.y + 1][coord.x]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y + 1][coord.x]);
            coord.y++;
        }
        break;
    }
    return coord;
}

Object_type Red::who()
{
    return RED_GHOST;
}