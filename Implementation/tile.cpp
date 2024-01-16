#include "tile.h"

Tile::Tile(int x, int y, World& world)
    : world(world)
{
    coord.x = x;
    coord.y = y;
}

Object_type Tile::who()
{
    return TILE;
}