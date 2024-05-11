#include "blue_ghost.h"

Object_type Blue::who() {
	return BLUE_GHOST;
}


Coord Blue::exit_house()
{
    swap(world[coord.y][coord.x], world[5][8]);
    coord.y = 5;
    coord.x = 8;
    exithouse = true;
    return coord;
}

Coord Blue::move(Coord player) {
    playerloc = player;
    Coord target;
    target.x = playerloc.x - coord.x;
    target.y = playerloc.y - coord.y;
    if (target.x > 0) {
        //try to Move right
        if ((coord.x + 1 < BOARD_WIDTH) && (world[coord.y][coord.x + 1]->who() != WALL)) {
            if ((world[coord.y][coord.x + 1]->who() == PLAYER))
            {
                world[coord.y][coord.x + 1]->set_lives(world[coord.y][coord.x + 1]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x + 1]);
            coord.x++;
            return coord;
        }
    }
    if (target.x < 0) {
        // try to Move left
        if ((coord.x > 0) && (world[coord.y][coord.x - 1]->who() != WALL)) {
            if ((world[coord.y][coord.x - 1]->who() == PLAYER))
            {
                world[coord.y][coord.x - 1]->set_lives(world[coord.y][coord.x - 1]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y][coord.x - 1]);
            coord.x--;
            return coord;
        }
    }
    if (target.y < 0) {
        // try to move up
        if ((coord.y > 0) && (world[coord.y - 1][coord.x]->who() != WALL)) {
            if ((world[coord.y - 1][coord.x]->who() == PLAYER))
            {
                world[coord.y - 1][coord.x]->set_lives(world[coord.y - 1][coord.x]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y - 1][coord.x]);
            coord.y--;
            return coord;
        }
    }
    if (target.y > 0) {
        // try to move down
        if ((coord.y + 1 < BOARD_HEIGHT) && (world[coord.y + 1][coord.x]->who() != WALL)) {
            if ((world[coord.y + 1][coord.x]->who() == PLAYER))
            {
                world[coord.y + 1][coord.x]->set_lives(world[coord.y + 1][coord.x]->get_lives() - 1);
                return coord;
            }
            swap(world[coord.y][coord.x], world[coord.y + 1][coord.x]);
            coord.y++;
            return coord;
        }

    }
    // Choose a random direction
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

void Blue::display(sf::RenderWindow& window) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.012, 0.011);
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    sf::Vector2f display_position;
    display_position.x = coord.x * 21.7;
    display_position.y = coord.y * 20.6;
    sprite.setPosition(display_position);
    if (dir == LEFT)
    {
        sprite.setScale(-0.012f, 0.011f);
    }
    window.draw(sprite);
}