#include "player.h"

void Player::move()
{
    if (lives < 1)
    {
        cout << "Lives End";
        exit(1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        //Want to move player up, check for collisions
        if ((coord.y > 0) && (world[coord.y - 1][coord.x]->who() != WALL))
        {

            if (world[coord.y - 1][coord.x]->who() == CANDY)
            {
                delete world[coord.y - 1][coord.x];
                world[coord.y - 1][coord.x] = new Tile(coord.y - 1, coord.x, world);
            }
            //If the tile contains a ghost
            if ((world[coord.y - 1][coord.x]->who() == RED_GHOST) || (world[coord.y - 1][coord.x]->who() == BLUE_GHOST) || (world[coord.y - 1][coord.x]->who() == GREEN_GHOST))
            {
                lives--;
            }
            dir = UP;
            swap(world[coord.y][coord.x], world[coord.y - 1][coord.x]);
            coord.y--;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        //Want to move player left, check for collisions
        if ((coord.x > 0) && (world[coord.y][coord.x - 1]->who() != WALL))
        {

            if (world[coord.y][coord.x - 1]->who() == CANDY)
            {
                delete world[coord.y][coord.x - 1];
                world[coord.y][coord.x - 1] = new Tile(coord.y, coord.x - 1, world);
            }
            if ((world[coord.y][coord.x - 1]->who() == RED_GHOST) || (world[coord.y][coord.x - 1]->who() == BLUE_GHOST) || (world[coord.y][coord.x - 1]->who() == GREEN_GHOST))
            {
                lives--;
            }
            dir = LEFT;
            swap(world[coord.y][coord.x], world[coord.y][coord.x - 1]);
            coord.x--;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // want to move player down, check for collisions
        if ((coord.y + 1 < BOARD_HEIGHT) && (world[coord.y + 1][coord.x]->who() != WALL))
        {

            if (world[coord.y + 1][coord.x]->who() == CANDY)
            {
                delete world[coord.y + 1][coord.x];
                world[coord.y + 1][coord.x] = new Tile(coord.y + 1, coord.x, world);
            }
            if ((world[coord.y + 1][coord.x]->who() == RED_GHOST) || (world[coord.y + 1][coord.x]->who() == BLUE_GHOST) || (world[coord.y + 1][coord.x]->who() == GREEN_GHOST))
            {
                lives--;
            }
            dir = DOWN;
            swap(world[coord.y][coord.x], world[coord.y + 1][coord.x]);
            coord.y++;
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        //want to move player right, check for collisions
        if ((coord.x + 1 < BOARD_WIDTH) && (world[coord.y][coord.x + 1]->who() != WALL))
        {

            if (world[coord.y][coord.x + 1]->who() == CANDY)
            {
                delete world[coord.y][coord.x + 1];
                world[coord.y][coord.x + 1] = new Tile(coord.y, coord.x + 1, world);
            }
            if ((world[coord.y][coord.x + 1]->who() == RED_GHOST) || (world[coord.y][coord.x + 1]->who() == BLUE_GHOST) || (world[coord.y][coord.x + 1]->who() == GREEN_GHOST))
            {
                lives--;
            }
            dir = RIGHT;
            swap(world[coord.y][coord.x], world[coord.y][coord.x + 1]);
            coord.x++;

        }
    }
    else {
        switch (dir)
        {
        case UP:
            if ((coord.y > 0) && (world[coord.y - 1][coord.x]->who() != WALL))
            {

                if (world[coord.y - 1][coord.x]->who() == CANDY)
                {
                    delete world[coord.y - 1][coord.x];
                    world[coord.y - 1][coord.x] = new Tile(coord.y - 1, coord.x, world);
                }
                if ((world[coord.y - 1][coord.x]->who() == RED_GHOST) || (world[coord.y - 1][coord.x]->who() == BLUE_GHOST) || (world[coord.y - 1][coord.x]->who() == GREEN_GHOST))
                {
                    lives--;
                }
                dir = UP;
                swap(world[coord.y][coord.x], world[coord.y - 1][coord.x]);
                coord.y--;
            }
            break;
        case LEFT:
            if ((coord.x > 0) && (world[coord.y][coord.x - 1]->who() != WALL))
            {
                if (world[coord.y][coord.x - 1]->who() == CANDY)
                {
                    delete world[coord.y][coord.x - 1];
                    world[coord.y][coord.x - 1] = new Tile(coord.y, coord.x - 1, world);
                }
                if ((world[coord.y][coord.x - 1]->who() == RED_GHOST) || (world[coord.y][coord.x - 1]->who() == BLUE_GHOST) || (world[coord.y][coord.x - 1]->who() == GREEN_GHOST))
                {
                    lives--;
                }
                dir = LEFT;
                swap(world[coord.y][coord.x], world[coord.y][coord.x - 1]);
                coord.x--;

            }
            break;
        case RIGHT:
            if ((coord.x + 1 < BOARD_WIDTH) && (world[coord.y][coord.x + 1]->who() != WALL))
            {
                if (world[coord.y][coord.x + 1]->who() == CANDY)
                {
                    delete world[coord.y][coord.x + 1];
                    world[coord.y][coord.x + 1] = new Tile(coord.y, coord.x + 1, world);
                }
                if ((world[coord.y][coord.x + 1]->who() == RED_GHOST) || (world[coord.y][coord.x + 1]->who() == BLUE_GHOST) || (world[coord.y][coord.x + 1]->who() == GREEN_GHOST))
                {
                    lives--;
                }
                dir = RIGHT;
                swap(world[coord.y][coord.x], world[coord.y][coord.x + 1]);
                coord.x++;

            }
            break;
        case DOWN:
            if ((coord.y + 1 < BOARD_HEIGHT) && (world[coord.y + 1][coord.x]->who() != WALL))
            {
                if (world[coord.y + 1][coord.x]->who() == CANDY)
                {
                    delete world[coord.y + 1][coord.x];
                    world[coord.y + 1][coord.x] = new Tile(coord.y + 1, coord.x, world);
                }
                if ((world[coord.y + 1][coord.x]->who() == RED_GHOST) || (world[coord.y + 1][coord.x]->who() == BLUE_GHOST) || (world[coord.y + 1][coord.x]->who() == GREEN_GHOST))
                {
                    lives--;
                }
                dir = DOWN;
                swap(world[coord.y][coord.x], world[coord.y + 1][coord.x]);
                coord.y++;
            }
            break;
        }
    }
}

Object_type Player::who()
{
    return PLAYER;
}

void Player::display(sf::RenderWindow& window)
{
    sf::CircleShape player(10.f);
    player.setFillColor(sf::Color::Yellow);
    sf::Vector2f display_position;
    display_position.x = coord.x * 20.5;
    display_position.y = coord.y * 20.6;
    player.setPosition(display_position);
    window.draw(player);
}